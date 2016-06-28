#ifndef CRSTATMANAGER_HPP
#define CRSTATMANAGER_HPP

#include "CRTypes.hpp"

namespace CRE
{
	class StatManager{
	public:

		StatManager();

		virtual ~StatManager();

		void register_app(App * theApp);

		int get_difficulty();

		void set_difficulty(int newDiff);

	private:

		//Copy constructor is private and undefined because we do not allow copies of StatManager
		StatManager(const StatManager &source);

		App * _theApp;

		int _diff;

	};
}

#endif