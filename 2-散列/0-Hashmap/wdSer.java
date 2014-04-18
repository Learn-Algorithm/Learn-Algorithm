import java.io.*;
import java.util.*;

public class wdSer {
	public static void main(String[] args) throws Exception {
		long startTime = System.currentTimeMillis();
        Map<String, Integer> map = new HashMap<String, Integer>();
        FileReader reader = new FileReader("inputfile.txt");
        BufferedReader br = new BufferedReader(reader);
        String str = null;
        while((str = br.readLine()) != null) {
            Integer count = map.get(str);
            map.put(str, count == null ? 1 : count + 1);
        }
        //System.out.println(map);
		long endTime = System.currentTimeMillis();
		System.out.println("Run time : " + (endTime - startTime)/1000 + "s");
	}
}