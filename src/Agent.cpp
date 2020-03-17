#include"Agent.h"
#include"Util.h"
#include <iostream>
using namespace std;

// creates the agent, sets the search algorithm of the agent
// do not change
Agent::Agent(char searchStr[])
{
	if (!strcmp(searchStr, "BFS"))
		searchType = BFS;
	else if (!strcmp(searchStr, "DFS"))
		searchType = DFS;
	else if (!strcmp(searchStr, "UCS"))
		searchType = UCS;
	else if (!strcmp(searchStr, "A_STAR"))
		searchType = A_STAR;
	else if (!strcmp(searchStr, "RAND"))
		searchType = RAND;
	else
		Util::Exit("Wrong search type/string in command line");
}

// sets the problem type
// do not change
void Agent::setProblemType(char problemType[])
{
	if (!strcmp(problemType, "eat-food"))
		problem = new MazeProblem();
	else if (!strcmp(problemType, "visit-corners"))
		problem = new CornersProblem();
	else if (!strcmp(problemType, "eat-all-foods"))
		problem = new AllFoodsMazeProblem();
	else
		Util::Exit("Wrong problem type in command line");
}

// reads layout file, sets the weather (costs), sets the initial state
// do not change
void Agent::perceive(char envFile[], char weatherType[])
{
	problem->readFromFile(envFile);
	problem->setCosts(weatherType);
	initState = problem->setInitState();
}

// calls the corresponding search functions
// do not change
void Agent::search()
{
	if (searchType == RAND)
		randomSearch();
	else
		graphSearch();
}

// fake/no search for now, random actions
// do not change
void Agent::randomSearch()
{
	Node *initNode = new Node(initState);
	Node *curNode = initNode;
	for (int i = 0; i < 100; i++)
	{
		State *curState = curNode->getState();
		vector<int> nextActions;
		vector<State *> nextStates;
		problem->getSuccessorStateActionPairs(nextStates, nextActions, curState);
		
		//
			for (int i = 0; i < nextActions.size(); i++)
			{
				cout << nextActions[i] << endl;
			}
			
		//
		//system("read");
		int randActIndex = rand() % nextActions.size();
		if (nextStates[randActIndex]->isSameState(curState))
		{
			i--;
			continue;
		}

		Node *newNode = new Node(nextStates[randActIndex]);
		newNode->setParentNode(curNode);
		newNode->action = nextActions[randActIndex];
		newNode->depth = curNode->depth++;
		newNode->pathCost = curNode->pathCost +
							problem->getStateActionCost(curNode->getState(), newNode->action);

		curNode->childNodes.push_back(newNode);
		curNode = newNode;
		if (problem->isGoalState(curNode->getState()))
		{
			break;
		}
	}
	solnNode = curNode;
}

// Prints the path (if msec>0) and prints out #
// do not change
void Agent::printSolution(int msec)
{
	if (solnNode == 0)
		cout << "NO SOLUTION FOUND" << endl;
	else
	{
		printPath(solnNode, msec);
	}
	cout << "# of expanded nodes: " << problem->getExpandedCount() << endl;
	cout << "path cost:" << solnNode->pathCost << endl;
}

// A recursive function that prints the path starting from the final node
// do not change
void Agent::printPath(Node *curNode, int msec)
{
	if (msec == -1)
		return;
	if (curNode->getParentNode() == 0)
	{
		usleep(msec * 400);
		system("clear");
		cout << "Weather: " << problem->getCostType() << endl
			 << endl;
		problem->printState(initState);
		return;
	}
	printPath(curNode->getParentNode(), msec);
	usleep(msec * 400);
	system("clear");
	cout << "Weather: " << problem->getCostType() << endl;
	cout << "ACTION:" << FSTARTBLU << problem->getActionName(curNode->action) << FEND << endl;
	problem->printState(curNode->getState());
}

// Implement for Q1-Q3 and use in the rest
void Agent::add2Fringe(Node *node)
{
	/********************* FILL-IN FROM HERE *********************/
	cout << "Inside add2Fringe(Node *node) ... Checking node's state... State is: " << ((MazeState*)node->getState())->agentPos << endl;
	cout << "Checking if type is UCS and if in closed list..." << endl;
	// if(searchType == UCS && isInClosedList(node))
	// {
	// 	for (int i = 0; i < closedList.size(); i++)
	// 	{
	// 		cout << "closedList[i]'s state is " << ((MazeState*)closedList[i]->getState())->agentPos << endl;
	// 		if(((MazeState*)closedList[i]->getState())->agentPos == ((MazeState*)node->getState())->agentPos)
	// 		{
	// 			cout << "same node is found in closedList!!! the state is: " <<  ((MazeState*)closedList[i]->getState())->agentPos << endl;
	// 			if(node->pathCost < closedList[i]->pathCost)
	// 			{
	// 				fringe.erase(fringe.begin()+i);
	// 				fringe.insert(fringe.begin()+i,node);
	// 			}
	// 			return;
	// 		}
	// 	}
	// }
	// else
	// {
		fringe.insert(fringe.begin(),node);
	//}
	/********************* FILL-IN UNTIL HERE *********************/
}

// Implement for Q1-Q3 and use in the rest
Node *Agent::removeFromFringe()
{
	cout << "Inside removeFromFringe() ..." << endl;
	Node *node = 0;
	if (searchType == BFS)
	{
		/********************* FILL-IN FROM HERE *********************/
		cout << "Inside BFS ..." << endl;
		node = fringe.back();
		cout << "node->depth is " << node->depth << endl;
		cout << "node's state is " << ((MazeState*)node->getState())->agentPos  << endl;
		//system("read");
		fringe.pop_back();
		cout << "node is removed from fridge" << endl;
		// Node *testNode = 0;	
		// testNode = fringe.back();
		// cout << "node->depth is " << node->depth << endl;
		/********************* FILL-IN UNTIL HERE *********************/
	}
	else if (searchType == DFS)
	{
		/********************* FILL-IN FROM HERE *********************/
		cout << "Inside DFS ..." << endl;
		node = fringe.front();
		cout << "node->depth is " << node->depth << endl;
		cout << "node's state is " << ((MazeState*)node->getState())->agentPos  << endl;
		//system("read");
		fringe.erase(fringe.begin());
		cout << "node is removed from fridge" << endl;
		// Node *testNode = 0;	
		// testNode = fringe.back();
		// cout << "node->depth is " << node->depth << endl;
		/********************* FILL-IN UNTIL HERE *********************/
	}
	else if (searchType == UCS)
	{

		/********************* FILL-IN FROM HERE *********************/
		cout << "Inside UCS ..." << endl;
		//system("read");
		double cheapestCost = fringe[0]->pathCost;
		cout << "after cheapest cost defintion ..." << endl;
		int cheapestIndex = 0;
		cout << "after cheapestIndex defintion ..." << endl;
		for (int i = 1; i < fringe.size(); i++)
		{
			cout << "fringe search...at index i: " << i << endl;
			cout << "fringe[i]'s pathCost: " << fringe[i]->pathCost << endl;
			if(cheapestCost > fringe[i]->pathCost)
			{
				cheapestCost = fringe[i]->pathCost;
				node = fringe[i];
				cheapestIndex = i;
			}
		}
		cout << "cheapestIndex is " << cheapestIndex <<endl;
		cout << "cheapest pathCost: " << fringe[cheapestIndex]->pathCost << endl;
		//system("read");
		node = fringe.at(cheapestIndex);
		cout << "node->depth is " << node->depth << endl;
		cout << "node's state is " << ((MazeState*)node->getState())->agentPos  << endl;
		fringe.erase(fringe.begin()+cheapestIndex);
		cout << "node is removed from fridge" << endl;
		/********************* FILL-IN UNTIL HERE *********************/
	}
	else if (searchType == A_STAR)
	{
		/********************* FILL-IN FROM HERE *********************/
		cout << "Inside A_STAR ..." << endl;
		//system("read");
		double cheapestCost = fringe[0]->pathCost + (int)problem->heuristicFunc(fringe[0]->getState());
		cout << "after cheapest cost defintion ..." << endl;
		int cheapestIndex = 0;
		cout << "after cheapestIndex defintion ..." << endl;
		for (int i = 1; i < fringe.size(); i++)
		{
			cout << "fringe search...at index i: " << i << endl;
			cout << "fringe[i]'s pathCost: " << fringe[i]->pathCost << endl;
			if(cheapestCost > fringe[i]->pathCost + (int)problem->heuristicFunc(fringe[i]->getState()))
			{
				cheapestCost = fringe[i]->pathCost + (int)problem->heuristicFunc(fringe[i]->getState());
				node = fringe[i];
				cheapestIndex = i;
			}
		}
		cout << "cheapestIndex is " << cheapestIndex <<endl;
		cout << "cheapest pathCost: " << fringe[cheapestIndex]->pathCost << endl;
		//system("read");
		node = fringe.at(cheapestIndex);
		cout << "node->depth is " << node->depth << endl;
		cout << "node's state is " << ((MazeState*)node->getState())->agentPos  << endl;
		fringe.erase(fringe.begin()+cheapestIndex);
		cout << "node is removed from fridge" << endl;
		/********************* FILL-IN UNTIL HERE *********************/
	}
	return node;
}

// Implement for Q1 and use in the rest
Node *Agent::graphSearch()
{
	Node *initNode = new Node(initState);
	cout << "Inside graphSearch..." << endl;
	initClosedList();
	//system("read");

	add2Fringe(initNode);
	/********************* FILL-IN FROM HERE *********************/
	while (true)
	{
		cout << "Inside while..." << endl;
		//system("read");
		if (fringe.empty())
		{
			cout << "fringe is empty!" << endl;
			return initNode;
		}
		cout << "before removeFromFringe() ..." << endl;
		Node *curNode = removeFromFringe();
		cout << "before isGoalState(curNode->getState()) ..." << endl;
		if (problem->isGoalState(curNode->getState()))
		{
			cout << "current node is in GOAL STATE!!!" << endl;
			solnNode = curNode;
			return curNode;
		}
		else
		{
			cout << "inside not in (in else) isGoalState(curNode->getState()) ..." << endl;
		}

		cout << "checking if in closedList " << endl;
		if (!isInClosedList(curNode))
		{
			cout << "detected not in closedList ..." << endl;
			cout << "before add2ClosedList(curNode) ..." << endl;
			add2ClosedList(curNode);
			cout << "before curNode->expand(problem) ..." << endl;
			curNode->expand(problem);
			cout << "after curNode->expand(problem) ..." << endl;
			cout << "entering the loop to traverse child nodes and add them to fringe ..." << endl;
			for (int i = 0; i < curNode->childNodes.size(); i++)
			{
				cout << "adding child " << i << " to fringe" << endl;
				add2Fringe(curNode->childNodes[i]);
			}
			cout << "end of !isInClosedList... " << endl;
 		}
		else
		{
			cout << "the node is already in closedList with state: " << ((MazeState*)curNode->getState())->agentPos << endl;
		}
		cout << "end of while " << endl;
	
	}
	cout << "after while " << endl;
	/********************* FILL-IN UNTIL HERE *********************/
}

void Agent::add2ClosedList(Node *node)
{
	/********************* FILL-IN FROM HERE *********************/
	cout << "inside add2ClosedList(curNode) ..." << endl;
	closedList.push_back(node);
	cout << "current node is added to closedList ..." << endl;
	/********************* FILL-IN UNTIL HERE *********************/
}

void Agent::initClosedList()
{
	/********************* FILL-IN FROM HERE *********************/
	closedList.clear();
	/********************* FILL-IN UNTIL HERE *********************/
}

bool Agent::isInClosedList(Node *node)
{
	/********************* FILL-IN FROM HERE *********************/
	for (int i = 0; i < closedList.size(); i++)
	{
		cout << "inside isInClosedList... " << endl;
		cout << "closedList[i]'s state is " << ((MazeState*)closedList[i]->getState())->agentPos << endl;
		if(((MazeState*)closedList[i]->getState())->agentPos == ((MazeState*)node->getState())->agentPos)
		{
			cout << "same node is found in closedList!!! Return isInClosedList as true" << endl;
			return true;
		}
	}
	cout << "same node is NOT found!!! Return isInClosedList as false" << endl;
	return false;
	
	
	// if(find(closedList.begin(), closedList.end(), node) != closedList.end())
	// {
	// 	cout << "same node is found in closedList!!! Return isInClosedList as true" << endl;
	// 	return true;
	// }
	// else
	// {
	// 	cout << "same node is NOT found!!! Return isInClosedList as false" << endl;
	// 	return false;
	// }
	/********************* FILL-IN UNTIL HERE *********************/
}

/******************* SEARCH TREE NODES **********************/

Node::Node(State *state)
{
	this->state = state;
	parentNode = 0;
	depth = 0;
	pathCost = 0;
	action = -1;
	f_n = g_n = h_n = 0;
}

void Node::expand(Problem *problem)
{
	// DO NOT REMOVE THIS CODE FROM HERE!
	if (parentNode)
	{
		if (f_n < parentNode->f_n)
		{
			problem->printState(parentNode->getState());
			problem->printState(state);
			Util::Exit("Inconsistent heuristics!");
		}
	}
	// DO NOT REMOVE THIS CODE UNTIL HERE!

	/********************* FILL-IN FROM HERE *********************/
	cout << "inside expand(Problem *problem) ..." << endl;
	State *curState = this->getState();
	vector<int> nextActions;
	vector<State *> nextStates;
	cout << "before getSuccessorStateActionPairs() ..." << endl;
	problem->getSuccessorStateActionPairs(nextStates, nextActions, curState);

	cout << "before for loop which traverses next actions ..." << endl;
	for (int i = 0; i < nextActions.size(); i++)
	{
		cout << "next action is " << nextActions[i] << endl;
		cout << "inside for loop which traverses next actions ..." << "i is " << i << endl;
		if (nextStates[i]->isSameState(curState))
		{
			cout << "inside isSameState" << endl; 
			continue;
		}

		Node *newNode = new Node(nextStates[i]);
		newNode->setParentNode(this);
		newNode->action = nextActions[i];
		cout << "action is " << newNode->action << endl; 
		newNode->depth = this->depth++;
		newNode->pathCost = this->pathCost +
							problem->getStateActionCost(this->getState(), newNode->action);
		
		this->childNodes.push_back(newNode);
		cout << "a child node is pushed to childNodes!" << endl;
		cout << "the child node's state is: " << ((MazeState*)childNodes.back()->getState())->agentPos << endl; 
	}
	/********************* FILL-IN UNTIL HERE *********************/
}
