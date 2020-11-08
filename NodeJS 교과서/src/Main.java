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