import java.math.BigInteger;
import java.util.ArrayList;


import java.math.BigInteger;
import java.util.*;

public class ThreeLevelCache extends TwoLevelCache {

    /** L3 cache variables*/
    /** 업그레이드를 위해 추가된 부분*/
    int offsetLength3, indexLength3, tagLength3, miss3 =0, hit3=0, index3;
    double hit_ratio3;
    String tag3, array3[];


    public ThreeLevelCache(int numberOfBlocks1, int bytesPerBlock1, int numberOfBlocks2, int bytesPerBlock2, int numberOfBlocks3, int bytesPerBlock3){
        super(numberOfBlocks1, bytesPerBlock1, numberOfBlocks2,bytesPerBlock2);


        /** This is for the l3 cache*/
        this.indexLength3 = (Integer.toBinaryString(numberOfBlocks3-1)).length();
        this.offsetLength3 = (Integer.toBinaryString(bytesPerBlock3-1)).length();
        this.tagLength2 = 16 - this.indexLength3 - this.offsetLength3;

        array3 = new String[numberOfBlocks3];		// this array will act as the cache
        for(int i=0;i<numberOfBlocks3;i++){	// this loop creates a list that will act as our cache
            array3[i] = "0";   // 0 Stand for invalid and one stands for valid, initial everything is invalid
        }

    }



    /** Return a value for the index in decimal for L3*/

    public int getIndex3(String address){
        String binaryIndex3 = address.substring(tagLength3, tagLength3 + indexLength3);
        return(Integer.parseInt(binaryIndex3, 2));
    }


    /** Return the value of a tag for L3*/
    public String getTag3(String address){

        return(address.substring(0, tagLength3));
    }

    public int getMisses3(){
        return miss3;
    }


    /** Return number of hits*/

    public int getHits3(){
        return hit3;
    }

    public double get_hitRatio_L3(){ return hit_ratio3;}

    public double get_TotalhitRatio(ArrayList<String> addresses)
    {
        total_hitRatio = (double)(hit1+hit2+hit3) / (addresses.size()) ;
        //total_hitRatio = Math.round(total_hitRatio*10000)/10000.0;
        return total_hitRatio;
    }

    /** Return number of cycles*/
    public int getCycles(){
        cycles = hit1 + (int)((1-hit_ratio1) * (hit2 + (int)((1-hit_ratio2) * (hit3 + (int)((1-hit_ratio3)*1000)))));
        return cycles;
    }


    /** This method checks on the L2 cache is there is content or not then do the relevant calculations */
    public void contentChecker2(String address){

        index2 = getIndex2(address);
        tag2 = getTag2(address);

        if(array2[index2].substring(0, 1).equals("0")){   // if it is invalid
            miss2 +=1;
            this.contentChecker3(address);
            array2[index2] = "1 " + tag2;
        }

        else{

            if(array2[index2].substring(2).equals(tag2)){
                hit2 +=1;
            }
            else{
                miss2 +=1;
                this.contentChecker3(address);
                array2[index2] = "1 " + tag2;
            }
        }

        hit_ratio2 = (double)hit2 / (double)(hit2+miss2);
        hit_ratio2 = Math.round(hit_ratio2*100)/100.0;
    }

    /** 업그레이드를 위해 추가된 부분 */
    public void contentChecker3(String address){

        index3 = getIndex3(address);
        tag3 = getTag3(address);

        if(array3[index3].substring(0, 1).equals("0")){   // if it is invalid
            miss3 +=1;
            array3[index3] = "1 " + tag3;
        }

        else{

            if(array3[index3].substring(2).equals(tag3)){
                hit3 +=1;
            }
            else{
                miss3 +=1;
                array2[index3] = "1 " + tag3;
            }
        }

        hit_ratio3 = (double)hit3 / (double)(hit3+miss3);
        hit_ratio3 = Math.round(hit_ratio3*100)/100.0;
    }
}