#pragma once

class Input {
	Input(unsigned long BlockID, unsigned long UTXOId) { this->BlockID = BlockID; this->UTXOId = UTXOId; }

private:
	unsigned long BlockID;
	unsigned long UTXOId;

};