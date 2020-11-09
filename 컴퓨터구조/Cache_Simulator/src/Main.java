import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Main {
	public static void main(String[] args) {
		
	//	String fileName = args[0];			    	// comment out this line from the command line
		String fileName = "heapsort.addr";     // uncomment this line to run on an IDE

		int l1NumberOfBlocks = 16, l1BytesPerBlock = 32;		// sets the L1 cache size
		int l2NumberOfBlocks = 64, l2BytesPerBlock = 64;		// sets the L2 cache size
		int l3NumberOfBlocks = 128, l3BytesPerBlock = 128;		// sets the L3 cache size
		
		ArrayList<String> addresses = new ArrayList<String>();  // this will store all addresses read from the file

		SingleLevelCache tempL1Cache = new SingleLevelCache(16,16); // This is just a dummy cache so i can be able to use the method in the single cache class

		BufferedReader file = null;
		
		try {	// Here we read a file and file store all addresses in an arrayList
			
			String line;
			file = new BufferedReader(new FileReader("Files/"+fileName));
			
			/** Adding each line on the array, converting it to decimal before*/
			while ((line = file.readLine()) != null) {

					addresses.add(tempL1Cache.hexToBin(line));
			}
		} 
		
		catch (IOException e) {
				System.out.println("File cannot be found");
		}


		
		System.out.println(fileName + " conatins " + addresses.size() + " instructions.");

		SingleLevelCache OneLevelCache = new SingleLevelCache(l1NumberOfBlocks, l1BytesPerBlock);	// Creating a new single cache object with giving blocks and block size
		OneLevelCache.contentChecker1(addresses);				// Calling the method that checks for content in the cache
		System.out.println("One level cache");
		System.out.println("L1 hits:       " +	OneLevelCache.getHits());
		System.out.println("L1 misses:     " +  OneLevelCache.getMisses());
		System.out.println(String.format("Total hit ratio: %.4f", OneLevelCache.get_hitRatio()));
		System.out.println("Cycles:     " +  OneLevelCache.getCycles());
		System.out.println("----------------------------------\n");

		TwoLevelCache TwoLevelCache = new TwoLevelCache(l1NumberOfBlocks, l1BytesPerBlock,l2NumberOfBlocks, l2BytesPerBlock);	// Creating a new single cache object with giving blocks and block sizes
		TwoLevelCache.contentChecker1(addresses);	// Calling the method that checks for content in the cache
		System.out.println("Two level cache");
		System.out.println("L1 hits:       " + TwoLevelCache.getHits1());
		System.out.println("L1 misses:     " + TwoLevelCache.getMisses1());
		System.out.println("L2 hits:       " + TwoLevelCache.getHits2());
		System.out.println("L2 misses:     " + TwoLevelCache.getMisses2());
		System.out.println(String.format("Total hit ratio: %.4f", TwoLevelCache.get_TotalhitRatio(addresses)));
		System.out.println("Cycles:        " + TwoLevelCache.getCycles());
		System.out.println("----------------------------------\n");

		// ------------------------------------------- 업그레이드한 부분 ------------------------------------------- 
		ThreeLevelCache ThreeLevelCache = new  ThreeLevelCache(l1NumberOfBlocks, l1BytesPerBlock,l2NumberOfBlocks, l2BytesPerBlock,l3NumberOfBlocks,l3NumberOfBlocks);	// Creating a new single cache object with giving blocks and block sizes
		ThreeLevelCache.contentChecker1(addresses);	// Calling the method that checks for content in the cache
		System.out.println("Three level cache");
		System.out.println("L1 hits:       " + ThreeLevelCache.getHits1());
		System.out.println("L1 misses:     " + ThreeLevelCache.getMisses1());
		System.out.println("L2 hits:       " + ThreeLevelCache.getHits2());
		System.out.println("L2 misses:     " + ThreeLevelCache.getMisses2());
		System.out.println("L3 hits:       " + ThreeLevelCache.getHits3());
		System.out.println("L3 misses:     " + ThreeLevelCache.getMisses3());
		System.out.println(String.format("Total hit ratio: %.4f", ThreeLevelCache.get_TotalhitRatio(addresses)));
		System.out.println("Cycles:        " + ThreeLevelCache.getCycles());
		System.out.println("----------------------------------\n");
	}
}
