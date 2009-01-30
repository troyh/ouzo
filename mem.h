typedef uint32_t docid_t;

class docid_list
{
	docid_t m_ids[10240];
	size_t m_count;
public:
	docid_list() :m_count(0) {}
	docid_list(char* p,size_t n) : m_count(0) 
	{
		m_count=std::min(sizeof(m_ids),n)/sizeof(docid_t);
		memcpy(m_ids,p,m_count*sizeof(docid_t));
	}
	~docid_list() {}
	
	const char* ptr() const { return (const char*)m_ids; }
	size_t ptrlen() const { return sizeof(docid_t)*m_count; }
	
	void add(docid_t docid)
	{
		m_ids[m_count++]=docid;
	}
	
	docid_t get(size_t n)
	{
		return m_ids[n];
	}
	
	size_t count() const { return m_count; }
	
};

