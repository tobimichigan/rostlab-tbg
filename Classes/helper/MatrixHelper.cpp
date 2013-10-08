/*
 * MatrixHelper.cpp
 *
 *  Created on: Oct 5, 2013
 *      Author: 'Sebastian Wilzbach <sebi@wilzbach.me>'
 */

#include "MatrixHelper.h"
#include "helper/HelperFunctions.h"

int ** MatrixHelper::scoringMatrix = new int*[20];
bool MatrixHelper::firstTime = false;

MatrixHelper::MatrixHelper() {
	// TODO Auto-generated constructor stub

}

MatrixHelper::~MatrixHelper() {
	// TODO Auto-generated destructor stub
	for (int i = 0; i < 20; ++i) {
		delete[] MatrixHelper::scoringMatrix[i];
	}
	delete[] MatrixHelper::scoringMatrix;
}

const char * MatrixHelper::getImagePathForAcid(char c) {
	const char * url;

	c = 'A';

	switch (c) {
	case 'A':
		url = "DAlanine.png";
		break;
	case 'C':
		url = "LArginine.png";
		break;
	case 'D':
		url = "LAsparagine.png";
		break;
	case 'E':
		url = "LAsparticAcid.png";
		break;
	case 'F':
		url = "LCysteine.png";
		break;
	case 'G':
		url = "LGlutamicAcid.png";
		break;
	case 'H':
		url = "LGlutamine.png";
		break;
	case 'I':
		url = "Glycine.png";
		break;
	case 'K':
		url = "DHistidine.png";
		break;
	case 'L':
		url = "LIsoleucine.png";
		break;
	case 'M':
		url = "LLeucine.png";
		break;
	case 'N':
		url = "LLysine.png";
		break;
	case 'P':
		url = "LMethione.png";
		break;
	case 'Q':
		url = "LPhenylalanine.png";
		break;
	case 'R':
		url = "DProline.png";
		break;
	case 'S':
		url = "LSerine.png";
		break;
	case 'T':
		url = "LThreonine.png";
		break;
	case 'V':
		url = "LTryptophan.png";
		break;
	case 'W':
		url = "LTyrosine.png";
		break;
	case 'Y':
		url = "LValine.png";
		break;
	}

	//add subfolder - NOT possible
	//std::string  temp= url;
	//std::string result = "" + temp;

	//cocos2d::CCLog("Path: %s", url);

	return url;
}

char MatrixHelper::getRandomAminoAcid() {
	int i = rand() % 20;
	char a;
	switch (i) {
	case 0:
		a = 'A';
		break;
	case 1:
		a = 'C';
		break;
	case 2:
		a = 'D';
		break;
	case 3:
		a = 'E';
		break;
	case 4:
		a = 'F';
		break;
	case 5:
		a = 'G';
		break;
	case 6:
		a = 'H';
		break;
	case 7:
		a = 'I';
		break;
	case 8:
		a = 'K';
		break;
	case 9:
		a = 'L';
		break;
	case 10:
		a = 'M';
		break;
	case 11:
		a = 'N';
		break;
	case 12:
		a = 'P';
		break;
	case 13:
		a = 'Q';
		break;
	case 14:
		a = 'R';
		break;
	case 15:
		a = 'S';
		break;
	case 16:
		a = 'T';
		break;
	case 17:
		a = 'V';
		break;
	case 18:
		a = 'W';
		break;
	case 19:
		a = 'Y';
		break;
	}

	return a;
}

int MatrixHelper::getScoreForAminoAcid(char c, char d) {
	int i = MatrixHelper::getAcidInt(c);
	int j = MatrixHelper::getAcidInt(d);
	if (j >= 0 && j <= 19 && i >= 0 && i <= 19) {
		return scoringMatrix[i][j];
	} else {
		return -1;
	}

}

/*
 * this method reads a matrix puts the data into an array
 * DO NOT MODIFY the reading part as long as it works
 * tested by Sebi
 * use the BLOSUM format as input
 */
void MatrixHelper::loadMatrix(std::string name) {

//	scoringMatrix = new int*[20];
	if (firstTime == false) {
		for (int i = 0; i < 20; i++) {
			/*if(scoringMatrix[i]){
			 delete[] scoringMatrix[i];
			 }*/
			scoringMatrix[i] = new int[20];
		}
		firstTime = true;
	}

	std::string pFileName = "matrices/"+name;
	char pMode = 'r';

	// Create input file stream
	// Initialize variables needed
	unsigned long fileSize = 0;
	unsigned char * fileContents = NULL;
	std::string thisLine, result, fullPath, contents;

	// Get absolute path of file
	fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(
			pFileName.c_str());

	cocos2d::CCLog("[ NOTICE ] Starting to read opening file: %s", pFileName.c_str());

	// Get data of file
	fileContents = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(
			fullPath.c_str(), "r", &fileSize);
	contents.append((char *) fileContents);

	// Create a string stream so that we can use getline( ) on it
	std::istringstream fileStringStream(contents);


	bool header = true;
	std::vector <int > acidOrder;
	acidOrder.resize(20);

	// Get file contents line by line
	while (getline(fileStringStream, thisLine)) {
		// Put all lines in vector
		//	mFileContents.push_back(thisLine);
		if (thisLine.at(0) == '#' ) {
			continue;
		}
		if(thisLine.at(0) == ' ' && header){
			std::vector < std::string > x = HelperFunctions::split(thisLine.c_str(),
							' ');

			int i=0;
			std::string  out ="";
			for (std::vector<std::string>::iterator it = x.begin() ; it != x.end(); ++it){
				if(i < 20 && (*it).size() > 0 ){
					char cd= (*it).at(0);
					acidOrder[i] = getAcidInt(cd);
					std::string str4 = static_cast<std::ostringstream*>(&(std::ostringstream()
												<< acidOrder[i]))->str();
					out = out +" "+  str4;
					i++;
				}
			}
			cocos2d::CCLog("Order of AA: %s", out.c_str());
			header = false;
		}

		int i = 0;
		int acidA = MatrixHelper::getAcidInt(thisLine.at(0));

		//check if AA is valid
		if(acidA < 0){
			continue;
		}

		//cocos2d::CCLog("AA: %c", thisLine.at(0));

		std::vector < std::string > x = HelperFunctions::split(thisLine.c_str(),
				' ');
		for (std::vector<std::string>::iterator it = x.begin(); it != x.end();
				++it) {


			std::string z = *it;
			/*	function to remove whitespace but not needed
			 * for (int i = 0; i < z.length(); i++) {
			 if (z[i] == ' ')
			 z.erase(i, 1);
			 } */

			if(z.size() > 0 ){
				int numb = atoi(z.c_str());
				// cocos2d::CCLog("%d", numb);
				if (i < 21 && i > 0) {
					scoringMatrix[acidA][acidOrder[i-1]] = numb;
				}
				i++;
			}
		}

	}

	// Delete buffer created by fileContents. This part is required.
	if (fileContents) {
		delete[] fileContents;
		fileContents = NULL;
	}

	for (int i = 0; i < 20; i++) {
		std::string timeStr = "";
		for (int j = 0; j < 20; j++) {
			timeStr = timeStr + " "
					+ static_cast<std::ostringstream*>(&(std::ostringstream()
							<< scoringMatrix[i][j]))->str();
		}
		cocos2d::CCLog("%s", timeStr.c_str());
	}

	// For testing purposes
	cocos2d::CCLog("[ NOTICE ] Finished opening file: %s", pFileName.c_str());

}

int MatrixHelper::getAcidInt(char c) {

	int n = -1;

	switch (c) {
	case 'A':
		n = 0;
		break;
	case 'C':
		n = 1;
		break;
	case 'D':
		n = 2;
		break;
	case 'E':
		n = 3;
		break;
	case 'F':
		n = 4;
		break;
	case 'G':
		n = 5;
		break;
	case 'H':
		n = 6;
		break;
	case 'I':
		n = 7;
		break;
	case 'K':
		n = 8;
		break;
	case 'L':
		n = 9;
		break;
	case 'M':
		n = 10;
		break;
	case 'N':
		n = 11;
		break;
	case 'P':
		n = 12;
		break;
	case 'Q':
		n = 13;
		break;
	case 'R':
		n = 14;
		break;
	case 'S':
		n = 15;
		break;
	case 'T':
		n = 16;
		break;
	case 'V':
		n = 17;
		break;
	case 'W':
		n = 18;
		break;
	case 'Y':
		n = 19;
		break;
	}
	return n;
}
