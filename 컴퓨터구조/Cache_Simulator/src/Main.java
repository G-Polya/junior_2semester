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

		SingleLevelCache oneLevelCache = new SingleLevelCache(l1NumberOfBlocks, l1BytesPerBlock);	// Creating a new single cache object with giving blocks and block size
		oneLevelCache.contentChecker1(addresses);				// Calling the method that checks for content in the cache
		System.out.println("One level cache");
		System.out.println("L1 hits:       " +	oneLevelCache.getHits1());
		System.out.println("L1 misses:     " +  oneLevelCache.getMisses1());
		System.out.println(String.format("Total hit ratio: %.4f", oneLevelCache.get_hitRatio()));
		System.out.println("Cycles:     " +  oneLevelCache.getCycles());
		System.out.println("----------------------------------\n");

		TwoLevelCache twoLevelCache = new TwoLevelCache(l1NumberOfBlocks, l1BytesPerBlock,l2NumberOfBlocks, l2BytesPerBlock);	// Creating a new single cache object with giving blocks and block sizes
		twoLevelCache.contentChecker1(addresses);	// Calling the method that checks for content in the cache
		System.out.println("Two level cache");
		System.out.println("L1 hits:       " + twoLevelCache.getHits1());
		System.out.println("L1 misses:     " + twoLevelCache.getMisses1());
		System.out.println("L2 hits:       " + twoLevelCache.getHits2());
		System.out.println("L2 misses:     " + twoLevelCache.getMisses2());
		System.out.println(String.format("Total hit ratio: %.4f", twoLevelCache.get_TotalhitRatio(addresses)));
		System.out.println("Cycles:        " + twoLevelCache.getCycles());
		System.out.println("----------------------------------\n");

		// ------------------------------------------- 업그레이드한 부분 ------------------------------------------- 
		ThreeLevelCache threeLevelCache = new  ThreeLevelCache(l1NumberOfBlocks, l1BytesPerBlock,l2NumberOfBlocks, l2BytesPerBlock,l3NumberOfBlocks,l3NumberOfBlocks);	// Creating a new single cache object with giving blocks and block sizes
		threeLevelCache.contentChecker1(addresses);	// Calling the method that checks for content in the cache
		System.out.println("Three level cache");
		System.out.println("L1 hits:       " + threeLevelCache.getHits1());
		System.out.println("L1 misses:     " + threeLevelCache.getMisses1());
		System.out.println("L2 hits:       " + threeLevelCache.getHits2());
		System.out.println("L2 misses:     " + threeLevelCache.getMisses2());
		System.out.println("L3 hits:       " + threeLevelCache.getHits3());
		System.out.println("L3 misses:     " + threeLevelCache.getMisses3());
		System.out.println(String.format("Total hit ratio: %.4f", threeLevelCache.get_TotalhitRatio(addresses)));
		System.out.println("Cycles:        " + threeLevelCache.getCycles());
		System.out.println("----------------------------------\n");
	}
}
