// Lab 5.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



using namespace std;

//SAVE/LOAD FUNCTION
fstream FSsavefile(".\\Data\\Save\\hotdog.sav");
string sFSBuffer;
//END SAVE/LOAD FUNCTION

//GLOBAL VARIABLES
int iFinish = 0;
int iLocation = 10;
string sInventory = "watch"; //Temp Inventory for testing, should start as a space or blank for final game
int iChore [5]= {0,0,0,0,0};
string sLastAction;
int iTakeCheck;
int iExistCheck;
int iMusic = 1;
//END GLOBAL VARIABLES

//ITEM STATES
string sBigItems[30] = {" "," "," "," "," "," "," "," "," "," ",
	                 "wide_table", // Room 10
					 "garbage_can car",
					 "",
					 "big_couch tv ottoman",
					 "bilard_table computer",
					 "small_couch picture coffee table",
					 "small_toilet small_sink bin",
					 "cabinets big_sink counter wood_floor",
					 "dinning_table china_cabinet", // Room 18
					 "",
					 "small_table", // Room 20
					 "",
					 "",
					 "zombie",
					 "big_bed mirror drawers trash_can",
					 "desk chair shelf bed rug",
					 "sink toilet small_cabinet basket shower",
					 "case weights treadmill little_box",
					 "box big_box bag",
					 "bench clothes"}; // Room 29

string sSmallItems[30] = {" "," "," "," "," "," "," "," "," "," ",
	                 "screwdriver", // Room 10
					 "desk_key",
					 "",
					 "bit_adapter",
					 "generic",
					 "book",
					 "cleaning_product",
					 "phone small_trash_bag",
					 "generic", // Room 18
					 "",
					 "car_keys", // Room 20
					 "",
					 "",
					 "generic",
					 "trash_bag",
					 "glasses",
					 "generic",
					 "cutlass",
					 "paper_towels old_tv",
					 "generic"}; // Room 29

int iTVScrew = 0;
int iZombDead = 0;
int iSinkClean = 0;
int iShowerClean = 0;
int iWatchOpen = 0;
int iTakeBatt = 0;
int iPhoneOn = 0;
int iTVInCan = 0;
int iPhoneCalled = 0;
int iDeskLocked = 0;
int iWearingGlasses = 0;
int iCarLocked = 0;
int iBookAttempt = 0;
int iBookRead = 0;
int iTrashOnFloor = 0;
int iTrashInBag = 0;
int iTrashInCan = 0;
//END ITEM STATES

//CONSOLE SIZE CODE
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//END CONSOLE SIZE CODE

void FToggleMusic()
{
	if (iMusic == 0)
	{
		PlaySound(TEXT(".\\Data\\Audio\\main.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
		iMusic = 1;
	}
	else
	{
		PlaySound(NULL, NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
		iMusic = 0;
	}
}
void FDispItems()
{
	int iPos = 0;
	int iLengthList;
	int iLengthNew;
	int iLengthLine = 55;
	int iLengthDif;
	string sTemp1;
	string sTemp2;
	string sList;

	sTemp1 = sBigItems[iLocation];
	sTemp2 = sBigItems[iLocation];
	while (iPos != -1)
	{
		iLengthList = sList.length();
		iPos = sTemp1.find(" ");
		if (iPos != -1)
		{
			sTemp1.erase(iPos, 1000);
			sTemp2.erase(0, iPos+1);
			iLengthNew = sTemp1.length();
			if ((iLengthList + iLengthNew + 2) < iLengthLine)
			{
				sList.append(sTemp1);
				sList.append(", ");
			}
			else
			{
				iLengthDif = iLengthLine - iLengthList;
				iLengthLine = 70;
				cout << sList;
				for (int s=0; s != iLengthDif + 1; s++)
				{
					cout << " ";
				}
				cout << "#  " << endl << "   # ";
				sList.clear();
				sList.append(sTemp1);
				sList.append(", ");
			}
			sTemp1 = sTemp2;
		}
		else
		{
			iLengthNew = sTemp1.length();
			if ((iLengthList + iLengthNew) < iLengthLine)
			{
				sList.append(sTemp1);
				iLengthList = sList.length();
				cout << sList;
				iLengthDif = iLengthLine - iLengthList;
				for (int s=0; s != iLengthDif + 1; s++)
				{
					cout << " ";
				}
				cout << "#  ";
			}
			else
			{
				iLengthDif = iLengthLine - iLengthList;
				iLengthLine = 70;
				cout << sList;
				for (int s=0; s != iLengthDif + 1; s++)
				{
					cout << " ";
				}
				cout << "#  " << endl << "   # ";
				sList.clear();
				sList.append(sTemp1);
				iLengthList = sList.length();
				cout << sList;
				iLengthDif = iLengthLine - iLengthList;
				for (int s=0; s != iLengthDif + 1; s++)
				{
					cout << " ";
				}
				cout << "#  ";
			}
		}
	}
}

void FLocDiscrpt()
{
	cout << endl << endl << "   ##########################################################################  " << endl
		                 << "   #                                                                        #  " << endl
	                     << "   # SURROUNDINGS:                                                          #  " << endl
		                 << "   # -------------                                                          #  " << endl;
	switch (iLocation) 
	{
		case 10:
		cout << "   # You are in the Main Hall.                                              #  " << endl
		     << "   # To the north is the Small Hall, to the east is the Family Room, to the #  " << endl
			 << "   # south is the Front Door, and to the west is the Garage. There are      #  " << endl
			 << "   # stairs leading up here.                                                #  " << endl;
		break;

		case 11:
		cout << "   # You are in the Garage.                                                 #  " << endl
		     << "   # To the east is the Main Hall, and to the south is the Garage Door.     #  " << endl;
		break;

		case 12:
		cout << "   # You are in the Small Hall.                                             #  " << endl
		     << "   # To the north is the Down Stairs Bathroom, to the east is the Living    #  " << endl
			 << "   # Room, to the south is the Main Hall, and to the west is the Lounge.    #  " << endl;
		break;

		case 13:
		cout << "   # You are in the Family Room.                                            #  " << endl
		     << "   # To the north is the Living Room, and to the west is the Main Hall.     #  " << endl;
		break;

		case 14:
		cout << "   # You are in the Lounge.                                                 #  " << endl
		     << "   # To the north is the Dinning Room, and to the east is the Small Hall.   #  " << endl;
		break;

		case 15:
		cout << "   # You are in the Living Room.                                            #  " << endl
		     << "   # To the north is the Kitchen, to the south is the Family Room, and to   #  " << endl
			 << "   # west is the Small Hall.                                                #  " << endl;
		break;

		case 16:
		cout << "   # You are in the Down Stairs Bathroom.                                   #  " << endl
		     << "   # To the south is the Small Hall.                                        #  " << endl;
		break;

		case 17:
		cout << "   # You are in the Kitchen.                                                #  " << endl
		     << "   # To the south is the Living Room, and to the west is the Dinning Room.  #  " << endl;
		break;

		case 18:
		cout << "   # You are in the Dinning Room.                                           #  " << endl
		     << "   # To the east is the Kitchen, and to the south is the Lounge.            #  " << endl;
		break;

		case 20:
		cout << "   # You are in the Main Upstairs Hall.                                     #  " << endl
		     << "   # To the north is the North Hall, to the east is the East Hall, and to   #  " << endl
			 << "   # the west is the West Hall. There are stairs leading down here.         #  " << endl;
		break;

		case 21:
		cout << "   # You are in the East Hall.                                              #  " << endl
		     << "   # To the south is the Rec Room, and to the west is the Main Upstairs     #  " << endl
			 << "   # Hall.                                                                  #  " << endl;
		break;

		case 22:
		cout << "   # You are in the West Hall.                                              #  " << endl
		     << "   # To the east is the Main Upstairs Hall, to the south is the Secondary   #  " << endl
			 << "   # Bedroom, and to the west is the Closet.                                #  " << endl;
		break;

		case 23:
		cout << "   # You are in the North Hall.                                             #  " << endl
		     << "   # To the east is the Master Bedroom, to the south is the Main Upstairs   #  " << endl
			 << "   # Hall, and to the west is your Bedroom.                                 #  " << endl;
		break;

		case 24:
		cout << "   # You are in the Master Bedroom.                                         #  " << endl
		     << "   # To the east is the Master Bathroom, and to the west is the North Hall. #  " << endl;
		break;

		case 25:
		cout << "   # You are in your Bedroom.                                               #  " << endl
		     << "   # To the east is the North Hall.                                         #  " << endl;
		break;

		case 26:
		cout << "   # You are in the Master Bathroom.                                        #  " << endl
		     << "   # To the west is the Master Bedroom.                                     #  " << endl;
		break;

		case 27:
		cout << "   # You are in the Rec Room.                                               #  " << endl
		     << "   # To the north is the East Hall.                                         #  " << endl;
		break;

		case 28:
		cout << "   # You are in the Closet.                                                 #  " << endl
		     << "   # To the east is the West Hall.                                          #  " << endl;
		break;

		case 29:
		cout << "   # You are in the Secondary Bedroom.                                      #  " << endl
		     << "   # To the north is the West Hall.                                         #  " << endl;
		break;
    }
		    cout << "   #                                                                        #  " << endl
			     << "   # Things Around: ";
		FDispItems();
	cout << endl << "   #                                                                        #  " << endl
	             << "   ##########################################################################  " << endl;

} 


int FItemExistRemove(string sItem, int iRem)
{
	int iLength = sItem.length();
	int iBigCheck = sBigItems[iLocation].find(sItem);
	int iSmallCheck = sSmallItems[iLocation].find(sItem);
	if (iSmallCheck != -1 && iBigCheck == -1)
		iExistCheck = 1;
	else if(iSmallCheck == -1 && iBigCheck != -1)
		iExistCheck = 2;
	else
		iExistCheck = -1;
	if (iRem == 1 && iTakeCheck != -1 && iBigCheck == -1 && iSmallCheck != -1)
	{
		if ((sItem != "phone" && sItem != "old_tv" && sItem != "desk_key" && sItem != "glasses" && sItem != "pile_of_trash") || ((sItem == "phone" && iPhoneOn == 1) ||(sItem == "old_tv" && iTVScrew == 1) || (sItem == "desk_key" && iCarLocked == 1) || (sItem == "glasses" && iDeskLocked == 1)))
		{
			if (iSmallCheck == 0)
				sSmallItems[iLocation].erase(iSmallCheck,iLength + 1);
			else
				sSmallItems[iLocation].erase(iSmallCheck - 1,iLength);
		}
	}
	if (iRem == 1 && iTakeCheck != -1 && iBigCheck != -1 && iSmallCheck == -1)
	{
		if (iBigCheck == 0)
			sBigItems[iLocation].erase(iBigCheck,iLength + 1);
		else
			sBigItems[iLocation].erase(iBigCheck - 1,iLength);
	}
	return iExistCheck;
}

void FRemoveInventory(string sInput)
{
	int iPos = sInventory.find(sInput);
	int iLength = sInput.length();
	if (iPos == 0)
		sInventory.erase(iPos,iLength + 1);
	else
		sInventory.erase(iPos - 1,iLength + 1);
}

int FGo(string sDirection)
{
	if (sDirection == "north")
	{
		if (iLocation == 10)
		{
			iLocation = 12;
			sLastAction = "You move north";
		}
		else if (iLocation == 12)
		{
			iLocation = 16;
			sLastAction = "You move north";
		}
		else if (iLocation == 13)
		{
			iLocation = 15;
			sLastAction = "You move north";
		}
		else if (iLocation == 14)
		{
			iLocation = 18;
			sLastAction = "You move north";
		}
		else if (iLocation == 15)
		{
			iLocation = 17;
			sLastAction = "You move north";
		}
		else if (iLocation == 20)
		{
			iLocation = 23;
			sLastAction = "You move north";
		}
		else if (iLocation == 27)
		{
			iLocation = 21;
			sLastAction = "You move north";
		}
		else if (iLocation == 29)
		{
			iLocation = 22;
			sLastAction = "You move north";
		}
		else
		{
			sLastAction = "You can't go that way!";
		}
	}
	else if (sDirection == "south")
	{
		if (iLocation == 12)
		{
			iLocation = 10;
			sLastAction = "You move south";
		}
		else if (iLocation == 15)
		{
			iLocation = 13;
			sLastAction = "You move south";
		}
		else if (iLocation == 16)
		{
			iLocation = 12;
			sLastAction = "You move south";
		}
		else if (iLocation == 17)
		{
			iLocation = 15;
			sLastAction = "You move south";
		}
		else if (iLocation == 18)
		{
			iLocation = 14;
			sLastAction = "You move south";
		}
		else if (iLocation == 21)
		{
			iLocation = 27;
			sLastAction = "You move south";
		}
		else if (iLocation == 22)
		{
			iLocation = 29;
			sLastAction = "You move south";
		}
		else if (iLocation == 23)
		{
			iLocation = 20;
			sLastAction = "You move south";
		}
		else
		{
			sLastAction = "You can't go that way!";
		}
	}
	else if (sDirection == "east")
	{
		if (iLocation == 10)
		{
			iLocation = 13;
			sLastAction = "You move east";
		}
		else if (iLocation == 11)
		{
			iLocation = 10;
			sLastAction = "You move east";
		}
		else if (iLocation == 12)
		{
			iLocation = 15;
			sLastAction = "You move east";
		}
		else if (iLocation == 14)
		{
			iLocation = 12;
			sLastAction = "You move east";
		}
		else if (iLocation == 18)
		{
			iLocation = 17;
			sLastAction = "You move east";
		}
		else if (iLocation == 20)
		{
			iLocation = 21;
			sLastAction = "You move east";
		}
		else if (iLocation == 22)
		{
			iLocation = 20;
			sLastAction = "You move east";
		}
		else if (iLocation == 23)
		{
			if(iZombDead != 1)
			{
				sLastAction = "The zombie blocks your way";
			}
			else
			{
				iLocation = 24;
				sLastAction = "You move east";
			}
		}
		else if (iLocation == 24)
		{
			iLocation = 26;
			sLastAction = "You move east";
		}
		else if (iLocation == 25)
		{
			iLocation = 23;
			sLastAction = "You move east";
		}
		else if (iLocation == 28)
		{
			iLocation = 22;
			sLastAction = "You move east";
		}
		else
		{
			sLastAction = "You can't go that way!";
		}
	}
	else if (sDirection == "west")
	{
		if (iLocation == 10)
		{
			iLocation = 11;
			sLastAction = "You move west";
		}
		else if (iLocation == 12)
		{
			iLocation = 14;
			sLastAction = "You move west";
		}
		else if (iLocation == 13)
		{
			iLocation = 10;
			sLastAction = "You move west";
		}
		else if (iLocation == 15)
		{
			iLocation = 12;
			sLastAction = "You move west";
		}
		else if (iLocation == 17)
		{
			iLocation = 18;
			sLastAction = "You move west";
		}
		else if (iLocation == 20)
		{
			iLocation = 22;
			sLastAction = "You move west";
		}
		else if (iLocation == 21)
		{
			iLocation = 20;
			sLastAction = "You move west";
		}
		else if (iLocation == 22)
		{
			iLocation = 28;
			sLastAction = "You move west";
		}
		else if (iLocation == 23)
		{
			iLocation = 25;
			sLastAction = "You move west";
		}
		else if (iLocation == 24)
		{
			iLocation = 23;
			sLastAction = "You move west";
		}
		else if (iLocation == 26)
		{
			iLocation = 24;
			sLastAction = "You move west";
		}
		else
		{
			sLastAction = "You can't go that way!";
		}
	}
	else
	{
		sLastAction = "Invalid direction";
	}

	return iLocation;
}

void FInventory()
{
	string sInvTemp1 = sInventory;
	string sInvTemp2 = sInventory;
	int iPos = 0;
	sLastAction = "(Checked Inventory)";
	system("cls");
	cout << "Inventory Contents" << endl
		 << "------------------" << endl;

	while (iPos != -1 ) 
	{
		iPos = sInvTemp1.find(" ");
	 	if (iPos != -1 )
		{
			sInvTemp1.erase(iPos,1000);
			sInvTemp2.erase(0,iPos +1);
			cout << sInvTemp1 << endl;
			sInvTemp1 = sInvTemp2;
		}
		else
			cout << sInvTemp1;
	}
	cout << endl << endl << "Press Enter to continue...";
	
	cin.get();
	system("cls");
}

void FUse(string sObjInv, string sObjEnv)
{
	int iInv;

	if (sObjEnv != "nil" && sObjEnv != "watch")
	{
		iInv = sInventory.find(sObjInv);
		FItemExistRemove(sObjEnv, 0);
		if (iInv == -1 && iExistCheck != -1)
			sLastAction = "You don't have a " + sObjInv + "!";
		if (iExistCheck == -1 && iInv != -1)
			sLastAction = "There is no " + sObjEnv + " here!";
		if (iInv == -1 && iExistCheck == -1)
			sLastAction = "You don't have a " + sObjInv + " and there is no " + sObjEnv + " here!";
		if (iInv != -1 && iExistCheck != -1)
			if (sObjInv == "screwdriver" && sObjEnv == "old_tv" && iTVScrew == 0)  //example outcomes for trying to use an object, change for final game
			{
				sLastAction = "You unscrew the tv from the floor";
				iTVScrew = 1;
			}
			else if (sObjInv == "cutlass" && sObjEnv == "zombie" && iZombDead == 0)
			{
				sLastAction = "You slay the foul creature!";
				FItemExistRemove("zombie", 1);
				iZombDead = 1;
			}
			else if (sObjInv == "cleaning_product" && (sObjEnv == "sink" || sObjEnv == "shower"))
			{
				sLastAction = "You don't have anything to wipe it off with!";
			}
			else if (sObjInv == "paper_towels" && (sObjEnv == "sink" || "shower"))
			{
				sLastAction = "You don't have any kind of cleaner or soap!";
			}
			else if (sObjInv == "cleaning_supplies" && sObjEnv == "sink" && iSinkClean == 0)
			{
				sLastAction = "You clean the sink";
				iSinkClean = 1;
			}
			else if (sObjInv == "cleaning_supplies" && sObjEnv == "shower" && iShowerClean == 0)
			{
				sLastAction = "You clean the shower";
				iShowerClean = 1;
			}
			else if (sObjInv == "old_tv" && sObjEnv == "garbage_can" && iTVInCan == 0)
			{
				sLastAction = "You throw the old crappy tv into the garbage";
				FRemoveInventory("old_tv");
				iTVInCan = 1;
			}
			else if (sObjInv == "watch_batteries" && sObjEnv == "phone" && iPhoneOn == 0)
			{
				sLastAction = "You place the batteries into the phone. It is now on";
				FRemoveInventory("watch_batteries");
				iPhoneOn = 1;
			}
			else if (sObjInv == "desk_key" && sObjEnv == "desk" && iDeskLocked == 0)
			{
				sLastAction = "You unlock your desk";
				iDeskLocked = 1;
			}
			else if (sObjInv == "car_keys" && sObjEnv == "car" && iCarLocked == 0)
			{
				sLastAction = "You unlock the car";
				iCarLocked = 1;
			}
			else if (sObjInv == "trash_bag" && sObjEnv == "pile_of_trash" && iTrashInBag == 0)
			{
				sLastAction = "You manage to scoup up the trash and place it into the new bag";
				FItemExistRemove("pile_of_trash", 1);
				iTrashInBag = 1;
			}
			else if (sObjInv == "trash_bag" && sObjEnv == "garbage_can" && iTrashInBag == 1 && iTrashInCan == 0)
			{
				sLastAction = "You toss the trash_bag into the garbage_can";
				FRemoveInventory("trash_bag");
				iTrashInCan = 1;
			}
			else
			{
				int iDenyPhrase;
				srand( time(0));
				iDenyPhrase = rand()%7+1; // Randomizing the number between 1-7.
				if (iDenyPhrase == 1)
					sLastAction = "Nope.";
				if (iDenyPhrase == 2)
					sLastAction = "Trust me, that won't work.";
				if (iDenyPhrase == 3)
					sLastAction = "If there is one thing I know its that that's not gonna happen.";
				if (iDenyPhrase == 4)
					sLastAction = "You can't do that";
				if (iDenyPhrase == 5)
					sLastAction = "You can't use that on that";
				if (iDenyPhrase == 6)
					sLastAction = "Sorry, you can't do that";
				if (iDenyPhrase == 7)
					sLastAction = "That can't be done";
			}
	}
	else if (sObjEnv == "watch")
	{
		if (sObjInv == "screwdriver" && sInventory.find("screwdriver") != -1 && iWatchOpen == 0 && sInventory.find("bit_adapter") != -1)
		{
			sLastAction = "You pop open the battery compartment of your watch and find two watch_batteries inside";
			iWatchOpen = 1;
		}
		else if (sObjInv == "screwdriver" && sInventory.find("screwdriver") == -1 && iWatchOpen == 0)
		{
			sLastAction = "You don't have a screwdriver!";
		}
		else if (sObjInv == "screwdriver" && sInventory.find("screwdriver") != -1 && iWatchOpen == 0 && sInventory.find("bit_adapter") == -1)
		{
			sLastAction = "The screws are too small for the screwdriver!";
		}
		else if (sObjInv == "screwdriver" && sInventory.find("screwdriver") != -1 && iWatchOpen == 1 && sInventory.find("bit_adapter") != -1)
		{
			sLastAction = "The watch is already open!";
		}
	}
	else
	{
		if (sObjInv == "stairs")
		{
			if(iLocation == 10)
			{
				iLocation = 20;
				sLastAction = "You're now upstairs";
			}
			else if(iLocation == 20)
			{
				iLocation = 10;
				sLastAction = "You're now downstairs";
			}
			else if(iLocation != 20 && iLocation != 10)
			{
				sLastAction = "The stairs aren't here!";
			}
		}
		else
		{
			iInv = sInventory.find(sObjInv);
			if (iInv == -1)
				sLastAction = "You don't have a " + sObjInv + "!";
			else
			{
				if (sObjInv == "phone")
				{
					if(iPhoneCalled == 0)
					{
						sLastAction = "You dial Chris on the phone and tell him 'SUP SON NEVER AGAIN'. He responds: 'NOOOOOOOOOOOOOOOOOOOO-' *click* you hang up the phone.";
						iPhoneCalled = 1;
					}
					else
						sLastAction = "You already called Chris!";
				}
				else if (sObjInv == "glasses")
				{
					if (iWearingGlasses == 0)
					{
						sLastAction = "You put on your glasses";
					    iWearingGlasses = 1;
					}
					else
						sLastAction = "You are already wearing your glasses!";
				}
				else if (sObjInv == "book")
				{
					if (iWearingGlasses == 0)
					{
						sLastAction = "You can't read it because you aren't wearing your glasses!";
					}
					else if (iBookAttempt == 0)
					{
						sLastAction = "You open the book to where you left off and try to read further, but you just can't bring yourself to do it";
						iBookAttempt++;
					}
					else if (iBookAttempt == 1)
					{
						sLastAction = "You really don't want to read any of this book";
						iBookAttempt++;
					}
					else if (iBookAttempt == 2)
					{
						sLastAction = "You read one page and then have to stop";
						iBookAttempt++;
					}
					else if (iBookAttempt == 3)
					{
						sLastAction = "JESUS CHRIST ALREADY!!! You manage to swallow your pride and read the remaining nine pages. Congratulations you lazy ass...";
						iBookAttempt++;
						iBookRead = 1;
					}
					else if (iBookAttempt == 4)
						sLastAction = "You have already read the ten pages you needed to";
				}
				else
					sLastAction = "That can't be used on its own!";
			}
		}

	}

}

void FTake(string sInput)
{
	int iDenyPhrase;
	srand( time(0));
	iDenyPhrase = rand()%7+1; // Randomizing the number between 1-7.

	iTakeCheck = sSmallItems[iLocation].find(sInput);
	FItemExistRemove(sInput, 1);

	if (iExistCheck != -1 || (iTakeBatt == 0 && iWatchOpen == 1))
	{
		if (iTakeCheck != -1 || sInput == "watch_batteries")
		{
			if (sInput == "old_tv" && iTVScrew == 0)
				sLastAction = "For some dumb reason it is screwed into the ground";
			else if (sInput == "phone" && iPhoneOn == 0)
				sLastAction = "The phone is no good to you dead";
			else if (sInput == "glasses" && iDeskLocked == 0)
				sLastAction = "There are no glasses here!";
			else if (sInput == "desk_key" && iCarLocked == 0)
				sLastAction = "The car is locked!";
			else if (sInput == "small_trash_bag")
			{
				sLastAction = "You pick up the small_trash_bag and pull it out of the kitchen cabinets but it tears and now there is a pile_of_trash on the wood_floor";
				sSmallItems[17].append(" ");
				sSmallItems[17].append("pile_of_trash");
				iTrashOnFloor = 1;
			}
			else if (sInput == "pile_of_trash")
				sLastAction = "You need something to carry it in!";
			else if (sInput == "watch_batteries" && iTakeBatt == 0)
			{
				sLastAction = "You take the batteries out of your watch";
				sInventory.append(" ");
				sInventory.append(sInput);
				iTakeBatt = 1;
			}
			else if (sInput == "paper_towels")
			{
				if (sInventory.find("cleaning_product") != -1)
				{
					sLastAction = "You take the paper_towels. The paper_towels and cleaning_product make cleaning_supplies!";
					sInventory.append(" ");
					sInventory.append("cleaning_supplies");
					FRemoveInventory("cleaning_product");
				}
				else
				{
					sLastAction = "You take the paper_towels";
					sInventory.append(" ");
					sInventory.append("paper_towels");
				}

			}
			else if (sInput == "cleaning_product")
			{
				if (sInventory.find("paper_towels") != -1)
				{
					sLastAction = "You take the cleaning_product. The paper_towels and cleaning_product make cleaning_supplies!";
					sInventory.append(" ");
					sInventory.append("cleaning_supplies");
					FRemoveInventory("paper_towels");
				}
				else
				{
					sLastAction = "You take the cleaning_product";
					sInventory.append(" ");
					sInventory.append("cleaning_product");
				}
			}
			else
			{
				sLastAction = "You pickup the " + sInput + ".";
				sInventory.append(" ");
				sInventory.append(sInput);
			}
		}
		else
		{
			if (iDenyPhrase == 1)
				sLastAction = "Nope.";
			if (iDenyPhrase == 2)
				sLastAction = "Trust me, you don't want that.";
			if (iDenyPhrase == 3)
				sLastAction = "If there is one thing I know its that that's not for you.";
			if (iDenyPhrase == 4)
				sLastAction = "You can't take that";
			if (iDenyPhrase == 5)
				sLastAction = "You can't pick that up";
			if (iDenyPhrase == 6)
				sLastAction = "Sorry, you can't have that";
			if (iDenyPhrase == 7)
				sLastAction = "That can't be taken";
		}
	}
	else
		sLastAction = "There is no " + sInput + " here!";
}

void FLook(string sInput)
{
	FItemExistRemove(sInput, 0);
	int iExisInv = sInventory.find(sInput);

	if (iExistCheck != -1 || iExisInv != -1)
	{
		if (sInput == "watch") 
		{
			if (iWatchOpen == 1 && iTakeBatt == 0)
				sLastAction = "Its a silver watch that you've had for a while. Still works! The battery compartment is open and has watch_batteries inside";
			else if (iWatchOpen == 0 && iTakeBatt == 0)
				sLastAction = "Its a silver watch that you've had for a while. Still works!";
			else
				sLastAction = "Its a silver watch that you've had for a while. It has stopped because there are no batteries";
		}
		if (sInput == "watch_batteries") 
			sLastAction = "They are fresh batteries you took from your watch";
		if (sInput == "screwdriver") 
			sLastAction = "A regular medium sized phillips screwdriver";
		if (sInput == "bit_adapter") 
			sLastAction = "A medium-to-small adapter bit for a phillips screwdriver";
		if (sInput == "cleaning_product") 
			sLastAction = "It is a typical multi-surface cleaning spray";
		if (sInput == "paper_towels") 
			sLastAction = "It is a thick roll of paper towels";
		if (sInput == "cleaning_supplies") 
			sLastAction = "Some paper towels and cleaning product that you can use to clean almost anything";
		if (sInput == "glasses") 
			sLastAction = "Regular rectangular rimemed glasses. You pretty much only need them for reading";
		if (sInput == "desk_key") 
			sLastAction = "The key to the desk in your room";
		if (sInput == "car_keys") 
			sLastAction = "The keys to the Hyundai in the garage";
		if (sInput == "book") 
			sLastAction = "It is your book from school. The Odyssey by Homer. Bleh";
		if (sInput == "trash_bag")
		{
			if (iTrashInBag == 0)
				sLastAction = "It is a large regular trash_bag with nothing in it";
			else
				sLastAction = "It is a large regular trash_bag with the kitchen trash in it";
		}
		if (sInput == "small_trash_bag") 
			sLastAction = "It is a small regular trash_bag with the kitchen trash in it";
		if (sInput == "wide_table") 
			sLastAction = "It is a wooden table by the door that holds various odds'n ends";
		if (sInput == "garbage_can") 
			sLastAction = "It is a big trash can for trash day";
		if (sInput == "car")
				sLastAction = "It is a grey 2002 Hyundai Sonata with a kick-ass stereo";
		if (sInput == "big_couch") 
			sLastAction = "It is nice leather couch that can fit four people";
		if (sInput == "tv") 
			sLastAction = "It is a 60in LED LCD TV that you got from Amazon";
		if (sInput == "ottoman") 
			sLastAction = "It is a small black ottoman that can act as a box and foot rest";
		if (sInput == "bilard_table") 
			sLastAction = "It is an expensive pool table with red felt. You've won many games here";
		if (sInput == "computer") 
			sLastAction = "It is a mildly old computer that your parents have kept in this room for browsing the web";
		if (sInput == "small_couch") 
			sLastAction = "It is a decently comfortible microfiber couch that can fit three people";
		if (sInput == "picture") 
			sLastAction = "It is a family portrait taken at the grand canyon";
		if (sInput == "coffee_table") 
			sLastAction = "It is a medium sized glass table with a mahogany bottom";
		if (sInput == "small_toilet") 
			sLastAction = "It is a regular old toilet";
		if (sInput == "small_sink") 
			sLastAction = "It is a single faucet ceramic sink";
		if (sInput == "bin") 
			sLastAction = "It is a small wooden bin with various items";
		if (sInput == "cabinets") 
			sLastAction = "They are various wooden cabinets on the wall in your kitchen";
		if (sInput == "big_sink") 
			sLastAction = "It is a large sink with some junk in it";
		if (sInput == "counter") 
			sLastAction = "It is large marble counter-top with various items";
		if (sInput == "wood_floor") 
			sLastAction = "It is the only hardwood flooring that you have in your house. Nice and shiny";
		if (sInput == "dinning_table") 
			sLastAction = "It is an expensive table that seats eight";
		if (sInput == "china_cabinet") 
			sLastAction = "A cabinet just for your mothers expensive china. Don't break it!";
		if (sInput == "small_table") 
			sLastAction = "It is a table for the convenience of keeping things on hand upstairs";
		if (sInput == "zombie") 
			sLastAction = "It is a gross, rotting zombie that doesn't look too friendly and is infront of your parent's room door. Not sure what he is doing there but he's there alright!";
		if (sInput == "big_bed") 
			sLastAction = "It is a king sized memory foam bed. Curse your selfish parents";
		if (sInput == "mirror") 
			sLastAction = "It is a large clean mirror made from steel";
		if (sInput == "drawers") 
			sLastAction = "They are drawers in the bureau's in the room. Probably hold clothes or something";
		if (sInput == "trash_can") 
			sLastAction = "It is a typical indoor trash can";
		if (sInput == "desk") 
			sLastAction = "It is your desk that you use to draw, work, and play games";
		if (sInput == "chair") 
			sLastAction = "It is your comfy rolling desk chair";
		if (sInput == "shelf") 
			sLastAction = "It is a shelf with various items on display";
		if (sInput == "bed") 
			sLastAction = "It is your twin size bed that you've had most of your life";
		if (sInput == "rug") 
			sLastAction = "It is a Fallout 3 themed rug. One of your prized possessions";
		if (sInput == "sink")
		{
			if(iSinkClean == 0)
				sLastAction = "It is a double faucet marble sink with some gold trim. It is a little dirty";
			else
				sLastAction = "It is a clean double faucet marble sink with some gold trim";
		}
		if (sInput == "toilet") 
			sLastAction = "It is a regular sized black toilet";
		if (sInput == "small_cabinet") 
			sLastAction = "It is an cabinet bellow the sink";
		if (sInput == "shower") 
		{
			if(iShowerClean == 0)
				sLastAction = "It is a large shower with a detachable nossle and bench. It is a little dirty";
			else
				sLastAction = "It is a clean large shower with a detachable nossle and bench";
		}
		if (sInput == "case") 
			sLastAction = "It is a weapon case from some time ago. Probably for collectors";
		if (sInput == "weights") 
			sLastAction = "They are various exercise weights ranging from 5lbs to 200lbs";
		if (sInput == "treadmill") 
			sLastAction = "It is a treadmill in pretty good shape";
		if (sInput == "little_box") 
			sLastAction = "It is a small box with various items";
		if (sInput == "box") 
			sLastAction = "It is a closed cardboard box";
		if (sInput == "big_box") 
			sLastAction = "It is a large cardboard box with something sticking out";
		if (sInput == "bag") 
		    sLastAction = "It is a small plastic bag";
		if (sInput == "bench") 
			sLastAction = "It is an old bench your paretns dont use anymore";
		if (sInput == "clothes") 
			sLastAction = "It is a pile of dirty clothes";
	}
	else
		sLastAction = "There is no " + sInput + " here, and you aren't carrying one either!";
}

void FSearch(string sInput)
{
	int iDenyPhrase;
	FItemExistRemove(sInput, 0);
	srand( time(0));
	iDenyPhrase = rand()%7+1; // Randomizing the number between 1-7.

	if (iExistCheck != -1)
	{
		if (sInput == "wide_table" && sInventory.find("screwdriver") == -1)
			sLastAction = "There is a screwdriver on top";
		//else if (sInput == "garbage_can") 
		//	sLastAction = "It is a big trash can for trash day";
		else if (sInput == "car" && sInventory.find("desk_key") == -1)
		{
			if (iCarLocked == 0)
				sLastAction = "The car is locked but you can see your desk_key on the passenger seat";
			if (iCarLocked == 1)
				sLastAction = "You can see your desk_key on the passenger seat";
		}
		//else if (sInput == "big_couch") 
		//	sLastAction = "It is nice leather couch that can fit four people";
		//else if (sInput == "tv") 
		//	sLastAction = "It is a 60in LED LCD TV that you got from Amazon";
		else if (sInput == "ottoman" && sInventory.find("ottoman") == -1) 
			sLastAction = "There is a bit_adapter inside";
		//else if (sInput == "bilard_table") 
		//	sLastAction = "It is an expensive pool table with red felt. You've won many games here";
		//else if (sInput == "computer") 
		//	sLastAction = "It is a mildly old computer that your parents have kept in this room for browsing the web";
		else if (sInput == "small_couch") 
			sLastAction = "Your book from school is resting on one of the arms";
		//else if (sInput == "picture") 
		//	sLastAction = "It is a family portrait taken at the grand canyon";
		//else if (sInput == "coffee_table") 
		//	sLastAction = "It is a medium sized glass table with a mahogany bottom";
		//else if (sInput == "small_toilet") 
		//	sLastAction = "It is a regular old toilet";
		//else if (sInput == "small_sink") 
		//	sLastAction = "It is a single faucet ceramic sink";
		else if (sInput == "bin" && (sInventory.find("cleaning_product") == -1 || sInventory.find("cleaning_supplies") == -1))
			sLastAction = "There is a bottle of cleaning_product inside";
		else if (sInput == "cabinets" && iTrashOnFloor == 0)
			sLastAction = "There is a small_trash_bag full of trash inside";
		//else if (sInput == "big_sink") 
		//	sLastAction = "It is a large sink with some junk in it";
		else if (sInput == "counter" && sInventory.find("phone") == -1) 
			sLastAction = "There is a phone on the counter. Its dead though, and for some reason takes watch batteries";
		else if (sInput == "wood_floor" && iTrashOnFloor == 1 && iTrashInBag == 0) 
			sLastAction = "There is a dirty pile_of_trash on the floor that came from the kitchen trash";
		//else if (sInput == "dinning_table") 
		//	sLastAction = "It is an expensive table that seats eight";
		//else if (sInput == "china_cabinet") 
		//	sLastAction = "A cabinet just for your mothers expensive china. Don't break it!";
		else if (sInput == "small_table" && sInventory.find("car_keys") == -1) 
			sLastAction = "The car_keys are resting on top";
		//else if (sInput == "zombie") 
		//	sLastAction = "It is a gross, rotting zombie that doesn't look too friendly and is infront of your parent's room door. Not sure what he is doing there but he's there alright!";
		//else if (sInput == "big_bed") 
		//	sLastAction = "It is a king sized memory foam bed. Curse your selfish parents";
		//else if (sInput == "mirror") 
		//	sLastAction = "It is a large clean mirror made from steel";
		//else if (sInput == "drawers") 
		//	sLastAction = "They are drawers in the bureau's in the room. Probably hold clothes or something";
		else if (sInput == "trash_can" && sInventory.find("trash_bag") == -1) 
			sLastAction = "There is a large empty trash_bag inside";
		else if (sInput == "desk" && sInventory.find("glasses") == -1)
		{
			if (iDeskLocked == 0)
				sLastAction = "The desk is locked";
			else
				sLastAction = "You find your glasses inside";
		}
		//else if (sInput == "chair") 
		//	sLastAction = "It is your comfy rolling desk chair";
		//else if (sInput == "shelf") 
		//	sLastAction = "It is a shelf with various items on display";
		//else if (sInput == "bed") 
		//	sLastAction = "It is your twin size bed that you've had most of your life";
		//else if (sInput == "rug") 
		//	sLastAction = "It is a Fallout 3 themed rug. One of your prized possessions";
		//else if (sInput == "sink")
		//	sLastAction = "It is a double faucet marble sink with some gold trim. It is a little dirty";
		//else if (sInput == "toilet") 
		//	sLastAction = "It is a regular sized black toilet";
		//else if (sInput == "small_cabinet") 
		//	sLastAction = "It is an cabinet bellow the sink";
		//else if (sInput == "shower") 
		//	sLastAction = "It is a large shower with a detachable nossle and bench. It is a little dirty";
		else if (sInput == "case" && sInventory.find("cutlass") == -1) 
			sLastAction = "You find a still sharp civil war era cutlass inside";
		//else if (sInput == "weights") 
		//	sLastAction = "They are various exercise weights ranging from 5lbs to 200lbs";
		//else if (sInput == "treadmill") 
		//	sLastAction = "It is a treadmill in pretty good shape";
		//else if (sInput == "little_box") 
		//	sLastAction = "It is a small box with various items";
		//else if (sInput == "box") 
		//	sLastAction = "It is a closed cardboard box";
		else if (sInput == "big_box" && sInventory.find("old_tv") == -1) 
			sLastAction = "There is your parents old_tv inside. Its a CRT.";
		else if (sInput == "bag" && (sInventory.find("paper_towels") == -1 || sInventory.find("cleaning_supplies") == -1)) 
			sLastAction = "You find a roll of paper_towels inside";
		//else if (sInput == "bench") 
		//	sLastAction = "It is an old bench your paretns dont use anymore";
		//else if (sInput == "clothes") 
		//	sLastAction = "It is a pile of dirty clothes";
		else
		{
			if (iDenyPhrase == 1)
				sLastAction = "Nothing.";
			if (iDenyPhrase == 2)
				sLastAction = "Trust me, the " + sInput + " is hiding nothing.";
			if (iDenyPhrase == 3)
				sLastAction = "If there is one thing I know its that there's nothing there.";
			if (iDenyPhrase == 4)
				sLastAction = "There's nothing to find";
			if (iDenyPhrase == 5)
				sLastAction = "There isn't anything there";
			if (iDenyPhrase == 6)
				sLastAction = "Sorry, there's nothing";
			if (iDenyPhrase == 7)
				sLastAction = "That doesn't have anything else";
		}
	}
	else
		sLastAction = "There is no " + sInput + " here!";
}

void FHelp()
{
	sLastAction = "(Checked Help Screen)";
	system("cls");
	cout << endl
		 << "Command Use:" << endl
		 << "------------" << endl
		 << "- go (direction) i.e. 'go north'" << endl
		 << "  This will move you from your current location to the next in any of the" << endl
		 << "  4 cardinal directions (assuming you can move in that direction)" << endl
		 << "- inventory" << endl
		 << "  This will display the contents of your inventory" << endl
		 << "- use (object) on (object) i.e. 'use rod on socket'" << endl
		 << "  This will use an object in your inventory on an object in the enviroment." << endl
		 << "  Additionally you can just do use (object) to use it on yourself" << endl
		 << "- look at (object) i.e. 'look at car'" << endl
		 << "  This will give a detailed description of an object in the enviroment or your" << endl
		 << "  inventory" << endl
		 << "- search (object) i.e. 'search mailbox'" << endl
		 << "  This will have you attempt to search an object in the enviroment" << endl
		 << "- chores" << endl
		 << "  This will display the chores you have left to complete" << endl
		 << "- toggle music" << endl
		 << "  This will toggle the game music on/off" << endl
		 << "- save" <<endl
		 << "  This will save your game. The previous save is overwritten" <<endl
		 << "- load" <<endl
		 << "  This will load your game from the save file" <<endl
		 << "- help" << endl
		 << "  This will redisplay these command instructions" << endl << endl
		 << "Note that commands are case sensitive" << endl << endl
		 << "Press Enter to contiune...";
		cin.get();
		system("cls");
}

void FChores()
{
	sLastAction = "(Checked Remaining Chores)";
	system("cls");
	cout << endl
		 << "Chores Left:" << endl
		 << "------------" << endl;
	if (iChore[0] == 0)
         cout << "(1) - Clean the upstairs bathroom" << endl; 
	if (iChore[1] == 0)
		 cout << "(2) - Move old mini TV into the garage garbage can" << endl;
	if (iChore[2] == 0)
		cout  << "(3) - Take the trash that's in the kitchen into the garage can" << endl; 
	if (iChore[3] == 0)
		cout  << "(4) - Call Chris and tell him 'never again'" << endl;
	if (iChore[4] == 0)
		 cout << "(5) - Read 10 pages out of your school book" << endl;
		 
	cout << endl << "Press Enter to contiune...";
		cin.get();
		system("cls");
}
void FChoreCheck()
{
	if(iSinkClean == 1 && iShowerClean == 1)
		iChore[0] = 1;
	if(iTVInCan == 1)
		iChore[1] = 1;
	if(iTrashInCan == 1)
		iChore[2] = 1;
	if(iPhoneCalled == 1)
		iChore[3] = 1;
	if(iBookRead == 1)
		iChore[4] = 1;

	if(iChore[0] == 1 && iChore[1] == 1 && iChore[2] == 1 && iChore[3] == 1 && iChore[4] == 1)
		iFinish = 1;
}

void FEndGame()
{

	PlaySound(NULL, NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	PlaySound(TEXT(".\\Data\\Audio\\ending.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	
	system("cls");
	cout << sLastAction << endl << endl <<
		    "With this all five of your chores are complete..." << endl << endl
	     << "Press Enter to contiune...";
	cin.get();
	system("cls");

	cout << "   With all of your chores done you feel like you have aged ten years and" << endl
		 << "that your stomach has all but dried and shattered to pieces. Victorious, you" << endl
		 << "approach the tyrant that is your dad saying 'I HAVE DONE THY DIRTY WORK NOW" << endl
		 << "BRINGITH ME MY HOT DOG!'. You feel proud in this moment, proud that agaisnt" << endl
		 << "all odds you still have brought justice to your poor aching appetite. But the" << endl
		 << "gods were not as pleased, and at that moment you faintly hear the petrifying" << endl
		 << "words 'Sorry... I am too tired now...' drift out of your dads mouth. And just" << endl
		 << "like that, you fall to your knees and crumble... to dust..." << endl << endl
		 << "Press Enter to contiune...";
	cin.get();

	system("cls");
	cout << "                                 -------------                                 " << endl
	     << "                                 | GAME OVER |                                 " << endl
		 << "                                 -------------                                 " << endl << endl << endl << endl
		 << "                                 _,.-------.,_                                 " << endl
         << "                             ,;~'             '~;,                             " << endl
         << "                           ,;                     ;,                           " << endl
         << "                          ;                         ;                          " << endl
         << "                         ,'                         ',                         " << endl
         << "                        ,;                           ;,                        " << endl
         << "                        ; ;      .           .      ; ;                        " << endl
         << "                        | ;   ______       ______   ; |                        " << endl
		 << "                        |  `/~'     ~' . '~     '~\'  |                        " << endl
         << "                        |  ~  ,-~~~^~, | ,~^~~~-,  ~  |                        " << endl
         << "                         |   |        }:{        |   |                         " << endl
         << "                         |   !       / | \\       !   |                        " << endl
         << "                         .~  (__,.--' .^. '--.,__)  ~.                         " << endl
         << "                         |     ---;' / | \\ `;---     |                        " << endl
         << "                          \\__.       \\/^\\/       .__/                       " << endl
         << "                           V| \\                 / |V                          " << endl
         << "                            | |T~\\___!___!___/~T| |                           " << endl
         << "                            | |`IIII_I_I_I_IIII'| |                            " << endl
         << "                            |  \\,III I I I III,/  |                           " << endl
         << "                             \\   `~~~~~~~~~~'    /                            " << endl
         << "                               \\   .       .   /                              " << endl
         << "                                 \\.    ^    ./                                " << endl
         << "                                   ^~~~^~~~^                                   " << endl << endl << endl
		 << " Perhaps one day there will be one great enough to vanquish the dastardly      " << endl
		 << " Mr. Dad . Only time will tell...                                              " << endl << endl << endl
	     << "                    CREATED BY: Chris Heimlich (oblivioncth)                   " << endl << endl
		 << "                             Thanks for playing!                               " << endl << endl
		 << "Press Enter to exit...";
	cin.get();
}

void FSave()
{
	FSsavefile.open(".\\Data\\Save\\hotdog.sav");

	if (FSsavefile.is_open())
	{
		FSsavefile << iFinish << endl << iLocation << endl << iChore [0] << endl << iChore [1] << endl << iChore [2] << endl << iChore [3] << endl
			       << iChore [4] << endl << iTakeCheck << endl << iExistCheck << endl << iMusic << endl << iTVScrew << endl << iZombDead << endl << iSinkClean 
				   << endl << iShowerClean << endl << iWatchOpen << endl << iTakeBatt << endl << iPhoneOn << endl << iTVInCan << endl << iPhoneCalled 
				   << endl << iDeskLocked << endl << iWearingGlasses << endl << iCarLocked << endl << iBookAttempt << endl << iBookRead << endl << iTrashOnFloor 
				   << endl << iTrashInBag << endl << iTrashInCan << endl << sInventory << endl << sLastAction << endl << sBigItems[10] << endl << sBigItems[11]
		           << endl << sBigItems[12] << endl << sBigItems[13] << endl << sBigItems[14] << endl << sBigItems[15] << endl << sBigItems[16] << endl << sBigItems[17] 
				   << endl << sBigItems[18] << endl << sBigItems[20] << endl << sBigItems[21] << endl << sBigItems[22] << endl << sBigItems[23] << endl << sBigItems[24]
				   << endl << sBigItems[25] << endl << sBigItems[26] << endl << sBigItems[27] << endl << sBigItems[28] << endl << sBigItems[29] << endl << sSmallItems[10] 
		           << endl << sSmallItems[11]  << endl << sSmallItems[12] << endl << sSmallItems[13] << endl << sSmallItems[14] << endl << sSmallItems[15] 
				   << endl << sSmallItems[16] << endl << sSmallItems[17] << endl << sSmallItems[18] << endl << sSmallItems[20] << endl << sSmallItems[21] 
				   << endl << sSmallItems[22] << endl << sSmallItems[23] << endl << sSmallItems[24] << endl << sSmallItems[25] << endl << sSmallItems[26] 
				   << endl << sSmallItems[27] << endl << sSmallItems[28] << endl << sSmallItems[29];

		sLastAction = "(Saved Game)";
	}
	else
		sLastAction = "Error accessing save file. Be sure 'hotdog.sav' is in the Save directory";

	FSsavefile.close();
}

void FLoad()
{
	FSsavefile.open(".\\Data\\Save\\hotdog.sav");

	if (FSsavefile.is_open())
	{
		FSsavefile >> iFinish >> iLocation >> iChore [0] >> iChore [1] >> iChore [2] >> iChore [3]
			       >> iChore [4] >> iTakeCheck >> iExistCheck >> iMusic >> iTVScrew >> iZombDead >> iSinkClean 
				   >> iShowerClean >> iWatchOpen >> iTakeBatt >> iPhoneOn >> iTVInCan >> iPhoneCalled 
				   >> iDeskLocked >> iWearingGlasses >> iCarLocked >> iBookAttempt >> iBookRead >> iTrashOnFloor 
				   >> iTrashInBag >> iTrashInCan;
		getline(FSsavefile,sFSBuffer);
		getline(FSsavefile,sInventory);
		getline(FSsavefile,sLastAction);
		getline(FSsavefile,sBigItems[10]);
		getline(FSsavefile,sBigItems[11]);
		getline(FSsavefile,sBigItems[12]);
		getline(FSsavefile,sBigItems[13]);
		getline(FSsavefile,sBigItems[14]);
		getline(FSsavefile,sBigItems[15]);
		getline(FSsavefile,sBigItems[16]);
		getline(FSsavefile,sBigItems[17]);
		getline(FSsavefile,sBigItems[18]);
		getline(FSsavefile,sBigItems[20]);
		getline(FSsavefile,sBigItems[21]);
		getline(FSsavefile,sBigItems[22]);
		getline(FSsavefile,sBigItems[23]);
		getline(FSsavefile,sBigItems[24]);
		getline(FSsavefile,sBigItems[25]);
		getline(FSsavefile,sBigItems[26]);
		getline(FSsavefile,sBigItems[27]);
		getline(FSsavefile,sBigItems[28]);
		getline(FSsavefile,sBigItems[29]);
	    getline(FSsavefile,sSmallItems[10]);
		getline(FSsavefile,sSmallItems[11]);
		getline(FSsavefile,sSmallItems[12]);
		getline(FSsavefile,sSmallItems[13]);
		getline(FSsavefile,sSmallItems[14]);
		getline(FSsavefile,sSmallItems[15]);
		getline(FSsavefile,sSmallItems[16]);
		getline(FSsavefile,sSmallItems[17]);
		getline(FSsavefile,sSmallItems[18]);
		getline(FSsavefile,sSmallItems[20]);
		getline(FSsavefile,sSmallItems[21]);
		getline(FSsavefile,sSmallItems[22]);
		getline(FSsavefile,sSmallItems[23]);
		getline(FSsavefile,sSmallItems[24]);
		getline(FSsavefile,sSmallItems[25]);
		getline(FSsavefile,sSmallItems[26]);
		getline(FSsavefile,sSmallItems[27]);
		getline(FSsavefile,sSmallItems[28]);
		getline(FSsavefile,sSmallItems[29]);

		sLastAction = "(Loaded Game); Saved Action: " + sLastAction;
	}
	else
		sLastAction = "Error accessing save file. Be sure 'hotdog.sav' is in the Save directory";

	FSsavefile.close();
}

void FUserInpt()
{

	int iPos;
	string sInput;

	cout << endl << "Input: ";
	getline(cin, sInput);

	iPos = sInput.find("go");
	if (iPos == 0)
	{
		sInput.erase(0,3);
		iLocation = FGo(sInput);
	}
	else
	{
		iPos = sInput.find("inventory");
		if (iPos == 0)
			FInventory();
		else
		{
			iPos = sInput.find("use");
			if (iPos == 0)
			{
				string sObjInv;
				string sObjEnv;
				int iPosOn;
				sInput.erase(0,4);
				iPosOn = sInput.find("on");

				if(iPosOn != -1 && sInput != "phone")
				{
					sObjInv = sInput;
					sObjEnv = sInput;
					sObjInv.erase(iPosOn - 1,1000);
					sObjEnv.erase(0,iPosOn + 3);
					FUse(sObjInv, sObjEnv);
				}
				else
				{
					sObjInv = sInput;
					sObjEnv = "nil";
					FUse(sObjInv, sObjEnv);
				}
			}
			else
			{
				iPos = sInput.find("take");
				if (iPos == 0)
				{
					sInput.erase(0,5);
					FTake(sInput);
				}
				else
				{
					iPos = sInput.find("look");
					if (iPos == 0)
					{
						int iPosLook;
						iPosLook = sInput.find("at");
						if (iPosLook != -1)
						{
							sInput.erase(0,iPosLook + 3);
							FLook(sInput);
						}
						else
							sLastAction = "At what?";
					}
					else
					{
						iPos = sInput.find("search");
						if (iPos == 0)
						{
							sInput.erase(0,7);
							FSearch(sInput);
						}
						else
						{
							iPos = sInput.find("help");
							if (iPos == 0)
								FHelp();
							else
							{
								iPos = sInput.find("chores");
								if (iPos == 0)
									FChores();
								else
								{
									iPos = sInput.find("toggle music");
									if (iPos == 0)
										FToggleMusic();
									else
									{
										iPos = sInput.find("save");
										if (iPos == 0)
											FSave();
										else
										{
											iPos = sInput.find("load");
											if (iPos == 0)
												FLoad();
											else
											{
												sLastAction = "Invalid Command";
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}




int _tmain(int argc, _TCHAR* argv[])
{
	int iPause; //Pause and remove annoying txt

//CONSOLE CODE
SMALL_RECT windowSize = {0, 0, 79, 40};

    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	SetConsoleTitle(L"Hot Dog Quest!");

//END CONSOLE CODE

	PlaySound(TEXT(".\\Data\\Audio\\opening.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	int iChoice = 0;
	Opening:
	   cout << "                        ---------------------------                            " << endl
			<< "                        | Welcome to Hot Dog Quest|                            " << endl
			<< "                        ---------------------------                            " << endl << endl
			<< "                               ______________                                  " << endl
			<< "                            .-'              `-.                               " << endl
			<< "                           (____________________)                              " << endl
			<< "                            (                  )                               " << endl
			<< "                           ( `----------------' )                              " << endl
			<< "                            `------------------'                               " << endl << endl << endl << endl
			<< " (1) Start New Game                                                            " << endl
			<< " (2) Continue Game                                                             " << endl
			<< " (3) Credits                                                                   " << endl << endl
	        << " Choice: ";
	while (iChoice != 1 && iChoice != 2 && iChoice != 3)
	{
		cin >> iChoice;
		cin.get();
	}
	
	if (iChoice == 2)
	{
		iChoice = 0;
		FLoad();
		system("cls");
		PlaySound(NULL, NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
		PlaySound(TEXT(".\\Data\\Audio\\main.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
		goto Start;
	}

	if (iChoice == 3)
	{
		iChoice = 0;
		system("cls");
		cout << " CREDITS" << endl 
		     << " =======" << endl 
			 << " Developer: Chris Heimlich (oblivioncth)" << endl
			 << " Language : C++ (Microsoft Visual Studio 2010)" << endl
			 << " Purpose: 'Computer Science and Programming' Final Project" << endl
			 << " Music: - Opening: Guild Wars 2 Menu Music 8-bit" << endl
			 << "        - Main Song: Daft Punk 'All Night' 8-bit" << endl
			 << "        - Ending: 8-bit Boss Fight Music from YouTube" << endl << endl << endl
			 << " Press enter to return...";
		cin.get();
		system("cls");
		goto Opening;
	}
	system("cls");
		
	cout << " STORY" << endl 
		 << " =====" << endl 
	     << "   As a 14 year old boy in 8th grade you find that you are often hungry, and at" << endl 
		 << "this particular moment you are VERY hungry. It's 5 o'clock, the time your dad" << endl 
		 << "usually gets you a hot dog, but he is being stubborn. You yell 'DAYYYYY GET ME" << endl
		 << "MY HOT DOG', but he's steadfast and tells you that you must do some chores" << endl 
		 << "before he will get one for you. You curse the heavens. 'WHY MUST MY DAD HINDER" << endl
		 << "ME SO!?' you shout. But you remain resolute, as you know that the only way you" << endl
		 << "will ever receive your pork-crafted delicacy is if you do his bidding..." << endl << endl
		 << "Press Enter to continue...";

	cin.get();
	system("cls");

	cout << "Your dad has left you with 5 chores:" << endl 
		 << "(1) - Clean the upstairs bathroom" << endl 
		 << "(2) - Move old mini TV into the garage garbage can" << endl
		 << "(3) - Take the trash that's in the kitchen into the garage can" << endl 
		 << "(4) - Call Chris and tell him 'never again'" << endl
		 << "(5) - Read 10 pages out of your school book" << endl << endl
		 << "Press Enter to continue...";
	
	cin.get();
	system("cls");

	cout << "The objective of the game is to complete your chores so that your dad will get" << endl
		 << "your hot dog. You have several commands at your disposal to help you do this:" << endl
		 << "- go (direction) i.e. 'go north'" << endl
		 << "  This will move you from your current location to the next in any of the" << endl
		 << "  4 cardinal directions (assuming you can move in that direction)" << endl
		 << "- inventory" << endl
		 << "  This will display the contents of your inventory" << endl
		 << "- use (object) on (object) i.e. 'use rod on socket'" << endl
		 << "  This will use an object in your inventory on an object in the enviroment." << endl
		 << "  Additionally you can just do use (object) to use it on yourself" << endl
		 << "- look at (object) i.e. 'look at car'" << endl
		 << "  This will give a detailed description of an object in the enviroment or your" << endl
		 << "  inventory" << endl
		 << "- search (object) i.e. 'search mailbox'" << endl
		 << "  This will have you attempt to search an object in the enviroment" << endl
		 << "- chores" << endl
		 << "  This will display the chores you have left to complete" << endl
		 << "- toggle music" << endl
		 << "  This will toggle the game music on/off" <<endl
		 << "- save" <<endl
		 << "  This will save your game. The previous save is overwritten" <<endl
		 << "- load" <<endl
		 << "  This will load your game from the save file" <<endl
		 << "- help" << endl
		 << "  This will redisplay these command instructions" << endl << endl
		 << "Note that commands are case sensitive" << endl << endl
		 << "Press Enter to contiune...";
	cin.get();
	system("cls");

	PlaySound(NULL, NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	PlaySound(TEXT(".\\Data\\Audio\\main.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);

	Start:
	while (iFinish == 0)
	{
		cout << "Last Action:" << endl
			 << "------------" << endl
			 << sLastAction;
		FLocDiscrpt();
		FUserInpt();
		system("cls");
		FChoreCheck();
	}

	FEndGame();
	goto Exit;	                                                                                    

	cin >> iPause; //Pause and remove annoying txt
	Exit:
	return 0;
}

