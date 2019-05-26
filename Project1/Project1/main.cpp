#include <iostream>
#include <nlohmann/json.hpp>
#include "Block.h"

using namespace std;

int main(void) {
	 
	nlohmann::json j;
	
	
	

}

Block createBlock(nlohmann::json j) {

	MerkleRoot root(j["ID"]);
	MerkleBlock* l = new MerkleBlock(j["nodes"][0]["ID"]);
	MerkleBlock* r = new MerkleBlock(j["nodes"][1]["ID"]);

	root.setFirstChildren(l, r);
	nlohmann::json l_s = j["nodes"][0];
	nlohmann::json r_s = j["nodes"][1];


}

/*void createBlockRec(MerkleBlock*mb, nlohmann::json j) {
	if (!j["trasaction"].empty()) {
		return new MerkleBlock()
	}
}*/
