import java.math.BigInteger;
import java.util.*;

public class TwoLevelCache extends SingleLevelCache{

	double total_hitRatio;

	/** L2 cache variables*/
	int offsetLength2, indexLength2, tagLength2, miss2 =0, hit2=0, index2;
	double hit_ratio2;
	String tag2, array2[];

	/** Constructor that will initialize the length of offset, index and tag*/
	public TwoLevelCache(int numberOfBlocks1, int bytesPerBlock1, int numberOfBlocks2, int bytesPerBlock2){
		super(numberOfBlocks1, bytesPerBlock1);

		/** This is for the l2 cache*/
		this.indexLength2 = (Integer.toBinaryString(numberOfBlocks2-1)).length();
		this.offsetLength2 = (Integer.toBinaryString(bytesPerBlock2-1)).length();
		this.tagLength2 = 16 - this.indexLength2 - this.offsetLength2;

		array2 = new String[numberOfBlocks2];		// this array will act as the cache
		for(int i=0;i<numberOfBlocks2;i++){	// this loop creates a list that will act as our cache
			array2[i] = "0";   // 0 Stand for invalid and one stands for valid, initial everything is invalid
		}
	}




	/** Return a value for the index in decimal for L2*/
	public int getIndex2(String address){

		String binaryIndex2 = address.substring(tagLength2, tagLength2 + indexLength2);
		return(Integer.parseInt(binaryIndex2, 2));
	}



	/** Return the value of a tag for L2*/
	public String getTag2(String address){

		return(address.substring(0, tagLength2));
	}


	public int getMisses2(){
		return miss2;
	}

	/** Return number of hits*/
	public int getHits2() {   return hit2;  }


	// hit_ratio를 계산하는 메소드 추가
	public double get_hitRatio_L1() { return hit_ratio1; }
	public double get_hitRatio_L2() { return hit_ratio2; }
	
	// 전체 hit ratio 계산메소드 추가
	public double get_TotalhitRatio(ArrayList<String> addresses)
	{
		total_hitRatio = (double)(super.hit1+hit2) / (addresses.size()) ;
		return total_hitRatio;
	}

	/** Return number of cycles*/
	// access time 계산 부분 수정. 
	public int getCycles(){
		cycles = hit1 + (int)((1-hit_ratio1) * (hit2 + (int)(1-hit_ratio2)*1000));
		return cycles;
	}

	/** This method checks on the L1 cache, and do relevant calculations. If there is no content it goes to L2 cache*/
	public void contentChecker1(ArrayList<String> addresses){

		/**Iterate through the array-list with addresses and check if they are on L1*/
		for(String address: addresses){

			index1 = getIndex1(address);
			tag1 = getTag1(address);

			if(array1[index1].substring(0, 1).equals("0")){   // if it is invalid
				miss1 +=1;
				this.contentChecker2(address);  // if there is a miss it goes to checks L2
				array1[index1] = "1 " + tag1;
			}

			else{

				if(array1[index1].substring(2).equals(tag1)){
					hit1 +=1;
				}
				else{
					miss1 +=1;
					this.contentChecker2(address);	// if there is a miss it goes to checks L2
					array1[index1] = "1 " + tag1;
				}
			}
		}
		hit_ratio1 = (double)hit1 / (double)(hit1+miss1);
		hit_ratio1 = Math.round(hit_ratio1*100) / 100.0;
	}

	/** This method checks on the L2 cache is there is content or not then do the relevant calculations */
	public void contentChecker2(String address){

		index2 = getIndex2(address);
		tag2 = getTag2(address);

		if(array2[index2].substring(0, 1).equals("0")){   // if it is invalid
			miss2 +=1;
			array2[index2] = "1 " + tag2;
		}

		else{

			if(array2[index2].substring(2).equals(tag2)){
				hit2 +=1;
			}
			else{
				miss2 +=1;
				array2[index2] = "1 " + tag2;
			}
		}

		hit_ratio2 = (double)hit2 / (double)(hit2+miss2);
		hit_ratio2 = Math.round(hit_ratio2*100) / 100.0;
	}
}