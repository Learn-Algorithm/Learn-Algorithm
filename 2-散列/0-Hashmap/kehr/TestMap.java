import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

class MyMap <K, V>
{
	private static int	  INIT_CAPACITY	= 16;	 
	private static float	LOAD_FACTOR	= 0.75f; 
	private int	          SIZE;	             
	private Entry<K, V>[]	table;	        
	private int	          MAX;	           
	                                      
	public MyMap()
	{
		this(INIT_CAPACITY, LOAD_FACTOR);
	}
	
	@SuppressWarnings("unchecked")
	public MyMap(int initialCapacity, float loadFactor)
	{
		if (initialCapacity < 0)
		    throw new IllegalArgumentException("Illegal initial capacity: "
		            + initialCapacity);
		
		if (loadFactor <= 0 || Float.isNaN(loadFactor))
		    throw new IllegalArgumentException("Illegal load factor: "
		            + loadFactor);
		MyMap.LOAD_FACTOR = loadFactor;
		MAX = (int) (initialCapacity * loadFactor);
		table = new Entry[initialCapacity];
	}
	
	public boolean put(K key, V value)
	{
		int hash = key.hashCode();
		Entry<K, V> temp = new Entry<K, V>(key, value, hash);
		
		if (setEntry(temp, table))
		{
			SIZE++;
			return true;
		}
		return false;
	}
	
	@SuppressWarnings("unchecked")
	private void reSize(int newSize)
	{
		Entry<K, V>[] newTable = new Entry[newSize];
		MAX = (int) (newSize * LOAD_FACTOR);
		for (int j = 0; j < table.length; j++)
		{
			Entry<K, V> entry = table[j];
			while (null != entry)
			{
				setEntry(entry, newTable);
				entry = entry.next;
			}
		}
		table = newTable;
		
	}
	
	private boolean setEntry(Entry<K, V> node, Entry[] table)
	{
		int index = indexFor(node.hash, table);
		Entry<K, V> entry = table[index];
		
		if (null != entry)
		{
			while (null != entry)
			{
				if ((node.key == entry.key || node.key.equals(entry.key))
				        && node.hash == entry.hash
				        && (node.value == entry.value || node.value
				                .equals(entry.value)))
				{
					return false;
				}
				
				else if (node.key == entry.key && node.value != entry.value)
				{
					entry.value = node.value;
					return true;
				}
				
				else if (node.key != entry.key)
				{
					if (null == entry.next)
					{
						break;
					}
					entry = entry.next;
				}
			}
			addEntryLast(entry, node);
			return true;
		}
		setFirstEntry(node, index, table);
		return true;
	}
	
	private void addEntryLast(Entry<K, V> entry, Entry<K, V> node)
	{
		if (SIZE > MAX)
		{
			reSize(table.length * 2);
		}
		entry.next = node;
		
	}
	
	private void setFirstEntry(Entry<K, V> node, int index, Entry[] table)
	{
		if (SIZE > MAX)
		{
			reSize(table.length * 2);
		}
		table[index] = node;
		node.next = null;
	}
	
	public V get(K key)
	{
		Entry<K, V> entry = null;
		int hash = key.hashCode();
		int index = indexFor(hash, table);
		entry = table[index];
		
		if (null == entry)
		{
			return null;
		}
		
		while (null != entry)
		{
			if (key == entry.key || entry.key.equals(key))
			{
				return entry.value;
			}
			entry = entry.next;
		}
		
		return null;
	}
	
	public int indexFor(int hashcode, Entry[] container)
	{
		return hashcode & (container.length - 1);
		
	}
	
	class Entry <K, V>
	{
		Entry<K, V>	next;
		K		    key;
		V		    value;
		int		    hash;
		
		Entry(K key, V value, int hash)
		{
			this.key = key;
			this.value = value;
			this.hash = hash;
			
		}
		@Override
		public String toString()
		{
			
			return key + "=" + value;
		}
	}
	

}

class TestMap
{
	
	public static void main(String[] args) throws IOException
	{
		String file = "/home/kehr/Github/Learn-Algorithm/2-散列/0-Hashmap/inputfile.txt";
		
		long startTime = System.currentTimeMillis();
		
		// MyMap<String, Integer> map = new MyMap<String, Integer>();
		HashMap<String, Integer> map = new HashMap<String, Integer>();
		
		FileReader reader = new FileReader(file);
		BufferedReader br = new BufferedReader(reader);
		String str = null;
		
		while ((str = br.readLine()) != null)
		{
			Integer count = map.get(str);
			map.put(str, count == null ? 1 : count + 1);
		}
		
		System.out.println(map);
		
		long endTime = System.currentTimeMillis();
		
		System.out.println("Run time : " + (endTime - startTime) / 1000 + "s");
	}
	
}
