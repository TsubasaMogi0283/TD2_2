#include "Record.h"

Record* Record::GetInstance() {
	static Record instance;
	return &instance;
}

Record::Record() {

}

Record::~Record() {

}

