#ifndef _EDDYLI_MAP_
#define _EDDYLI_MAP_
#include <iostream>
#include <string>

namespace eddyli {

	using std::string;

	template<class key_type, class value_type>
	class Bucket;

	template<class key_type, class value_type>
	class Map {

		public:
			Map(size_t bucket_size = 500, float fexpansivity = 0.75);
			value_type& insert(key_type& key, value_type& value);
			value_type* find(key_type& key);
			void print(Map map);
			value_type& operator[](key_type& key);

		private:
			unsigned MurmurHash2(const void* key,int len);
			unsigned djb_hash(const unsigned char *buf, int len);
			size_t hashcode(key_type& key, size_t mod);
			Bucket<key_type,value_type>* get_bucket(size_t code);
			void rehash();

		private:
			float fexpansivity;
			size_t ibucket_count;	   //bucket count
			size_t used;			   //buckets used
			Bucket<key_type, value_type>** buckets;		   //buckets
	};

	template<class key_type, class value_type>
	class Bucket {
		typedef struct Node {
			key_type key; //key
			int iprev;    //prev node
			int inext;	   //next node
			value_type value;     //value
		} Node;
		public:
			Bucket(size_t count = 5);
			value_type& put(key_type& key, value_type& value);
			value_type* get(key_type& key);
			size_t get_used();
			key_type* get_key();

		private:
			int inflate();
			Node* get_node_by_key(key_type* key);

		private:
			size_t m_used;    // value and node already used
			size_t m_icount;
			int    m_ihead;	  // head of list 
			Node*  m_buf;     // buf to store node
	};

	//========================================================================//

	template<class key_type, class value_type>
	Map<key_type, value_type>::Map(size_t bucket_size, float fexpansivity) {
		ibucket_count = bucket_size;
		this->fexpansivity = fexpansivity;
		used = 0;
		buckets = new (std::nothrow) Bucket<key_type,value_type>*[ibucket_count];
		memset(buckets, 0, sizeof(Bucket<key_type,value_type>*)*ibucket_count);
	}

	template<class key_type, class value_type>
	value_type& Map<key_type,value_type>::operator[](key_type& key) {
		value_type* v =  find(key);
		if (v == NULL) {
			v = new value_type();
			return insert(key, *v);
		}
		return *v;
	}
	template<class key_type, class value_type>
	Bucket<key_type,value_type>*  Map<key_type,value_type>::get_bucket(size_t code) {
		if (buckets[code] == NULL)
			buckets[code] = new (std::nothrow) Bucket<key_type,value_type>();
		return buckets[code];
	}

	template<class key_type, class value_type>
	value_type& Map<key_type,value_type>::insert(key_type& key, value_type& value) {
		int code = hashcode(key,ibucket_count);
		Bucket<key_type,value_type>* b = get_bucket(code);
		if (b->get_used() == 0)
			used++;
		value_type& v = b->put(key, value);
		if (used/(float)ibucket_count > fexpansivity)
			rehash();
		return v;
	}

	template<class key_type, class value_type>
	value_type* Map<key_type,value_type>::find(key_type& key) { 
		int code = hashcode(key, ibucket_count);
		Bucket<key_type,value_type>* b = get_bucket(code);
		value_type* value = b->get(key);
		return value;
	}

	template<class key_type, class value_type>
	void Map<key_type,value_type>::rehash() {
		size_t new_size = ibucket_count * 2;
		Bucket<key_type,value_type> **new_buckets = new (std::nothrow) Bucket<key_type,value_type>*[new_size];
		memset(new_buckets, 0, sizeof(Bucket<key_type,value_type>*) *new_size);

		for (size_t i = 0; i < ibucket_count; i++) {
			if (buckets[i] != NULL && buckets[i]->get_used() > 0) {
				key_type* key = buckets[i]->get_key();
				int code = hashcode(*key, new_size);
				new_buckets[code] = buckets[i];
			}
		}
		delete []buckets;
		buckets = new_buckets;
		ibucket_count = new_size;
	}

	template<class key_type, class value_type>
	void Map<key_type,value_type>::print(Map map) {
	
	}

	template<class key_type, class value_type>
	unsigned Map<key_type,value_type>::djb_hash(const unsigned char *buf, int len) {
		unsigned int hash = 5381;  
		while (len--)  
			hash = ((hash << 5) + hash) +(tolower(*buf++)); /* hash * 33 + c */  
		return hash;  
	}

	template<class key_type, class value_type>
	unsigned Map<key_type,value_type>::MurmurHash2(const void *key, int len) {
		/* 'm' and 'r' are mixing constantsgenerated offline. 
		They're not really 'magic', they justhappen to work well.  */  
		uint32_t seed = 5381;  
		const uint32_t m = 0x5bd1e995;  
		const int r = 24;  
   
		/* Initialize the hash to a 'random' value*/  
		uint32_t h = seed ^ len;  
   
		/* Mix 4 bytes at a time into the hash */  
		const unsigned char *data = (const unsigned char *)key;  
   
		while(len >= 4) {  
			uint32_t k = *(uint32_t*)data;  
   
			k *= m;  
			k ^= k >> r;  
			k *= m;  
   
			h *= m;  
			h ^= k;  
   
			data += 4;  
			len -= 4;  
		}  
   
		/* Handle the last few bytes of the inputarray  */  
		switch(len) {  
		case 3: h ^= data[2] << 16;  
		case 2: h ^= data[1] << 8;  
		case 1: h ^= data[0]; h *= m;  
		};  
   
		/* Do a few final mixes of the hash toensure the last few 
		 * bytes are well-incorporated. */  
		h ^= h >> 13;  
		h *= m;  
		h ^= h >> 15;  
   
		return (size_t)h;  
	}

	template<>
	size_t Map<std::string, int>::hashcode(std::string& key, size_t mod) {
		size_t code = MurmurHash2(key.c_str(), key.length());
		return code%mod;
	}

	template<class key_type, class value_type>
	Bucket<key_type, value_type>::Bucket(size_t count) {
		m_ihead = -1;
		m_used = 0;
		m_icount = count;
		m_buf = new Node[count];
	}

	template<class key_type, class value_type>
	key_type* Bucket<key_type, value_type>::get_key() {
		if (m_ihead != -1) {
			return &(m_buf[m_ihead].key);
		}
		return NULL;
	}

	template<class key_type, class value_type>
	int Bucket<key_type, value_type>::inflate() {
		size_t new_size = m_icount * 2;
		Node * buf = new Node[new_size];
		memset(buf, 0, sizeof(Node) * new_size);
		for (size_t i = 0; i < m_icount; i++) {
			buf[i] = m_buf[i];
		}
		m_icount = new_size;
		delete []m_buf;
		m_buf = buf;
		return 0;
	}

	template<class key_type, class value_type>
	value_type* Bucket<key_type, value_type>::get(key_type& key) {
		Node* p = get_node_by_key(&key);
		if(p != NULL) {
			return &p->value;
		}
		return NULL;
	}

	template<class key_type, class value_type>
	typename Bucket<key_type,value_type>::Node* Bucket<key_type, value_type>::get_node_by_key(key_type* key) {
		if(m_ihead == -1)
			return NULL;

		int index = m_ihead;
		while(index != -1) {
			if (!key->compare(m_buf[index].key))
				break;//found
			index = m_buf[index].inext;
		}
		if (index != -1)
			return &m_buf[index];
		return NULL;
	}

	template<class key_type, class value_type>
	value_type& Bucket<key_type, value_type>::put(key_type& key, value_type& value) {
		Node * free_node = &m_buf[m_used];
		free_node->key = key;
		free_node->value = value;
		free_node->iprev = -1;
		if (m_ihead == -1)
			free_node->inext = -1;
		else {
			free_node->inext = m_ihead;
			m_buf[m_ihead].iprev = m_used;
		}
		m_ihead = m_used;
		m_used += 1;
		if (m_used >= m_icount)
			inflate();
		return free_node->value;
	}

	template<class key_type, class value_type>
	size_t Bucket<key_type, value_type>::get_used() {
		return m_used;
	}
}

#endif
