#include<iostream>
#include<unordered_map>
#include<list>
#include<optional>
template<typename K,typename V>
class LRUCache{
private:
    using Node=std::pair<K,V>;
    using List_it=typename std::list<Node>::iterator;
    std::unordered_map<K,List_it> cache;
    std::list<Node> lru;
    size_t capacity;
public:
    explicit LRUCache(size_t capacity):capacity(capacity){}
    size_t size() const{
        return lru.size();
    }
    void put(const K& key,const V& value){
        auto it=cache.find(key);
        if(it!=cache.end()){
            auto list_it=it->second;
            list_it->second=value;
            lru.splice(lru.begin(),lru,list_it);  
        }else{
            lru.push_front({key,value});
            cache[key]=lru.begin();
        }

        if(lru.size()>capacity){
            K remove_key=lru.back().first;
            cache.erase(remove_key);
            lru.pop_back();
        }
    }
    std::optional<V> get(const K& key){
        auto it=cache.find(key);
        if(it!=cache.end()){
            auto list_it=it->second;
            lru.splice(lru.begin(),lru,list_it);
            
            return lru.front().second;    
        }
        return std::nullopt;
    }
};