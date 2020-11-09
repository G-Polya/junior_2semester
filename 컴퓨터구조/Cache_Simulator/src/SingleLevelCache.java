import java.math.BigInteger;
import java.util.*;

public class SingleLevelCache {

	int offsetLength1, indexLength1, tagLength1, miss1 =0, hit1 =0, index1, cycles;
	double hit_ratio1;
	String tag1, array1[];
	
	/** Constructor that will initialize the length of offset, index and tag*/
	public SingleLevelCache(int numberOfBlocks, int bytesPerBlock){
		
		this.indexLength1 = (Integer.toBinaryString(numberOfBlocks-1)).length();
		this.offsetLength1 = (Integer.toBinaryString(bytesPerBlock-1)).length();
		this.tagLength1 = 16 - this.indexLength1 - this.offsetLength1;
		
		array1 = new String[numberOfBlocks];		// this array will act as the cache

		for(int i=0;i<numberOfBlocks;i++){	// this loop creates a list that will act as our cache
			array1[i] = "0";   // 0 Stand for invalid and one stands for valid, initial everything is invalid
		}
	}
	
	/** This method will convert a hex value to binary and return it in 16 bits*/
	public String hexToBin(String s) { 
		
		 // This line does the actual convention but removes 0's in front
		  String binaryValue = new BigInteger(s, 16).toString(2);  
		  
		  // if the length is less than 16, we add zero's at the beginning
		  if(binaryValue.length()<16){  			
			  while(binaryValue.length()<16){
				  binaryValue = '0' + binaryValue;
			  }
		  }
		  return binaryValue;
	}
	
	/** Return a value for the index in decimal*/
	public int getIndex1(String address){
		
		String binaryIndex = address.substring(tagLength1, tagLength1 + indexLength1);
		return(Integer.parseInt(binaryIndex, 2));
				
	}
	
	/** Return the value of a tag*/
	public String getTag1(String address){
		
		return(address.substring(0, tagLength1));
	}
	
	/** Return number of misses*/
	public int getMisses1(){
		return miss1;
	}
	
	/** Return number of hits*/
	public int getHits1()  {  return hit1;	}
	public double get_hitRatio()
	{
		return hit_ratio1;
	}
	/** Return number of cycles*/
	public int getCycles(){
		cycles = hit1 + (int)((1- hit_ratio1) * 1000);
		return cycles;
	}
	
	public void contentChecker1(ArrayList<String> addresses){
		
		for(String address: addresses){

			index1 = getIndex1(address);
			tag1 = getTag1(address);
			
			if(array1[index1].substring(0, 1).equals("0")){   // if it is invalid
				miss1 +=1;
				array1[index1] = "1 " + tag1;
			}
				
			else{

				if(array1[index1].substring(2).equals(tag1)){
					hit1 +=1;
				}
				else{
					miss1 +=1;
					array1[index1] = "1 " + tag1;
				}
			}
			
		}

		hit_ratio1 = (double) hit1 /(double)(miss1 + hit1);
		//hit_ratio1 = Math.round(hit_ratio1 *10000) / 10000.0;
	}
}
