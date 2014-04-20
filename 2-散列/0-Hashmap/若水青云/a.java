package k;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.text.DecimalFormat;
import java.util.Vector;
import java.sql.*;
class hashmap
{
	public String key;
	public int value;
	public hashmap next;
	public int INF=300;
	public hashmap()
	{
		key=null;
		value=-1;
		next=null;
	}
	public hashmap(String k)
	{
		key=k;
		value=k.hashCode()%INF;
		next=null;
		if(a.s[value].next==null)
		{
			a.s[value].next=this;
		}
		else{
			next=a.s[value].next;
			a.s[value].next=this;
		}
	}
	public boolean search(String k)
	{
		int hash=k.hashCode()%INF;
		hashmap m=a.s[hash].next;
		while(m!=null)
		{
			if(k.equals(m.key))
				return true;
			m=m.next;
		}
		return false;
	}
	public void show()
	{
		System.out.println(value+" "+key);
	}
}
public class a
{
	static hashmap s[]=new hashmap[300];
	public static void main(String arg[]) throws IOException
	{
		for(int i=0;i<300;i++)
		{
			s[i]=new hashmap();
		}
		hashmap m;
		BufferedReader f1 = new BufferedReader(new InputStreamReader(new FileInputStream("G:\\inputfile.txt")));
		for (String line = f1.readLine(); line != null; line = f1.readLine()){
			System.out.println(line);
            m=new hashmap(line);
        }
		for(int i=0;i<300;i++)
		{
			m=s[i].next;
			while(m!=null)
			{
				System.out.println(m.value+" "+m.key);
				m=m.next;
			}
		}
	}
}