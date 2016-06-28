#include <assert.h>
#include "CRStatManager.hpp"
#include "CRConstants.hpp"
#include "CRApp.hpp"

namespace CRE{

	StatManager::StatManager() : _theApp(NULL), _diff(DIFF_EASY){

	}

	StatManager::~StatManager(){

	}

	void StatManager::register_app(App * theApp){

		// Check that our pointer is good
        assert(NULL != theApp and "StatManager::register_app() theApp pointer provided is bad");

        // Make a note of the pointer
        assert(NULL == _theApp and "StatManager::register_app() theApp pointer was already registered");

        _theApp = theApp;
	}

	int StatManager::get_difficulty(){
		return _diff;
	}

	void StatManager::set_difficulty(int newDiff){
		_diff = newDiff;
	}
}