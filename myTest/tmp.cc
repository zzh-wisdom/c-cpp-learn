#ifndef METASTORE_METASTORE_H
#define METASTORE_METASTORE_H

#include "art_tree.h"
#include "env.h"
#include "options.h"
#include "atomic.h"
#include <libpmem.h>
#include <string>
#include <atomic>

namespace dhms {
namespace metastore {

class MetaStore {
    static const uint64_t META_STORE_INITIALIZED = 0xDEADBEEFBEEFDEAD;
public:
    MetaStore(const char *path, uint64_t size, Options& opt, size_t key_size):
        art(), option(opt), k_size(key_size)
    {
        log_pool_path = opt.meta_data_area_dir_dpath + opt.meta_data_area_fname;
        log_pool_size = opt.meta_data_log_size;
        opt.env->PMFileMap(log_pool_path.c_str(), (size_t)log_pool_size, 
                           DHMS_ENV_FILE_CREATE, 0666, opt.pmem_adr_granularity, &map);
            
        assert(map != nullptr);

        uint64_t* head = (uint64_t*)(map->GetAddress());
        pool_addr = (uint64_t)head;
        log_head = (++head);
        if (*head == META_STORE_INITIALIZED) {
            // TODO: Recover & update log_head
            
        } else {
            *head = META_STORE_INITIALIZED;
            *log_head = 64;
        }

        art.setLoadKey(std::bind(pmLoadKeyWrapper, this, std::placeholders::_1, std::placeholders::_2));
    }
    MetaStore(const MetaStore&) = delete;
    MetaStore& operator=(const MetaStore&) = delete;

    ~MetaStore() {
        option.env->PMFileUnMap(&map);    
    }

    static void pmLoadKeyWrapper(MetaStore *store, TID tid, ArtKey &key) {
        store->pmLoadKey(tid, key);
    }

    void pmLoadKey(TID tid, ArtKey &key) {
        void* pkey = (void*)(uintptr_t)(tid + 1);
        key.set((char *)pkey, k_size);
    }

    inline ThreadInfo getThreadInfo() {
        return art.getThreadInfo();
    }

    inline TID lookup(const ArtKey &k, ThreadInfo &threadEpocheInfo) {
        return art.lookup(k, threadEpocheInfo) + 1 + k.getKeyLen();
    }

    inline void insert(const ArtKey &k, void *val, size_t vlen, ThreadInfo &epocheInfo) {
        uint64_t off = atmc_fetch_and_add64((unsigned long long*)log_head, k.getKeyLen() + vlen + 1);
        void* slot = (void*)(uintptr_t)(pool_addr + off);
        *(uint8_t*)slot = 1;
        void* pkey = (void*)(uintptr_t)(pool_addr + off + 1);
        memcpy(pkey, k.data, k.getKeyLen());
        void* pval = (void*)(uintptr_t)(pool_addr + off + 1 + k.getKeyLen());
        memcpy(pval, val, vlen);
        (map->GetPersistFn())(slot, k.getKeyLen() + vlen + 1);

        art.insert(k, (TID)(slot), epocheInfo);
    }
    
    inline void remove(const ArtKey &k, TID tid, ThreadInfo &epocheInfo) {
        void* slot = (void*)(uintptr_t)(tid - k.getKeyLen() - 1);
        *(uint8_t*)slot = 0;
        (map->GetPersistFn())(slot, k.getKeyLen() + 1);

        art.remove(k, (TID)(slot), epocheInfo);
    }
private:
    Art art;
    std::string log_pool_path;
    uint64_t log_pool_size;
    size_t k_size;
    uint64_t pool_addr;
    Options option;
    PMFileMapWrapper *map = nullptr;
    volatile uint64_t *log_head;
};

}
}

#endif
