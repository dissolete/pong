#ifndef CRCONSTANTS_HPP
#define CRCONSTANTS_HPP

namespace CRE
{

	//Status constants
	const int STATUS_OK = 0;
	const int STATUS_APP_INIT_FAILED = -1;
	const int STATUS_APP_STACK_EMPTY = -2;
	const int STATUS_ASSET_COULDNT_BE_LOADED = -3;
	const int STATUS_FONT_COULDNT_BE_LOADED = -4;

	//Other constants
	const int DIFF_EASY = 0;
	const int DIFF_NORMAL = 1;
	const int DIFF_HARD = 2;
}

#endif