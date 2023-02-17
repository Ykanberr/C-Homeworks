/* @Author Student Name: <Yavuz Kanber>
Student ID :<150170034>
Date: <13.11.2019> */
/*
PLEASE, DO NOT CHANGE void display(bool verbose, bool testing), int getUsableDay() and int getUsableTime() FUNCTIONS.
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS THAT IS MENTIONED ABOVE. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{		
	head = NULL;

}

void WorkPlan::close()
{
	Task* iter,*oter;
	while (head){
		(head->previous)->next = NULL;
		head->previous = NULL;
		iter = head;
		head = head->next;
		oter = iter->counterpart;
		while (oter) {
			iter->counterpart = NULL;
			delete iter;
			iter = oter;
			oter = oter->counterpart;
		}
		if (!oter) {
			delete iter;
		}
	}
}

void WorkPlan::add(Task* task)
{
	Task* add_task = new Task;
	add_task->day = task->day;
	add_task->priority = task->priority;
	add_task->time = task->time;
	int l = strlen(task->name);
	add_task->name = new char[l + 1];
	add_task->name[l] = '\0';
	for (int i = 0; i < l; i++) {
		add_task->name[i] = task->name[i];
	}
	if(head == NULL){
		head = add_task;
		head->previous = head;
		head->next = head;
		head->counterpart = NULL;
		return;
	}
	Task * traverse;
	if(head->day > add_task->day){
		add_task->next = head;
		(head->previous)->next = add_task;
		add_task->previous = head->previous;
		head->previous =add_task;
		add_task->counterpart = NULL;
		head = add_task;
		return;
	}
	if(add_task->day > (head->previous)->day){
		add_task->next = head;
		add_task->previous = head->previous;
		(head->previous)->next = add_task;
		head->previous = add_task;
		head->previous = add_task;
		add_task->counterpart = NULL;
		return;
	}
	traverse = head;
	while(traverse && add_task->day > traverse->day){
		traverse = traverse->next;
	}
	if(add_task->day == traverse->day){
		if(add_task->time < traverse->time){
			(traverse->next)->previous = add_task;
			(traverse->previous)->next = add_task;
			add_task->previous = traverse->previous;
			add_task->next = traverse->next;
			add_task->counterpart = traverse;
			traverse->next = NULL;
			traverse->previous = NULL;
			if (head->time > add_task->time && head->day == add_task->day) {
				head = add_task;
			}
			return;
		}
		Task* pretraverse = NULL;
		while(traverse && add_task->time > traverse->time){
			pretraverse = traverse;
			traverse = traverse->counterpart;
		}
		if (!traverse){
			pretraverse->counterpart = add_task;
			add_task->next = NULL;
			add_task->previous = NULL;
			add_task->counterpart = NULL;
			return;
		}
		if(add_task->time == traverse->time){
			if(add_task->priority > traverse->priority){
				if (!pretraverse) {
					add_task->next = traverse->next;
					add_task->previous = traverse->previous;
					traverse->next->previous = add_task;
					traverse->previous->next = add_task;
					add_task->counterpart = traverse->counterpart;
					checkAvailableNextTimesFor(traverse);
					traverse->time = usable_time;
					traverse->day = usable_day;
					add(traverse);
					return;
				}
				else {
					pretraverse->counterpart = add_task;
					add_task->counterpart = traverse->counterpart;
					add_task->next = NULL;
					add_task->previous = NULL;
					checkAvailableNextTimesFor(traverse);
					traverse->time = usable_time;
					traverse->day = usable_day;
					add(traverse);
					return;
				}
			}
			if(add_task->priority <= traverse->priority){
				if (!pretraverse) {
					add_task->next = traverse->next;
					add_task->previous = traverse->previous;
					traverse->next->previous = add_task;
					traverse->previous->next = add_task;
					add_task->counterpart = traverse->counterpart;
					checkAvailableNextTimesFor(traverse);
					traverse->time = usable_time;
					traverse->day = usable_day;
					traverse->next = add_task->next;
					traverse->previous = add_task->previous;
					add_task->next->previous = traverse;
					add_task->previous->next = traverse;
					traverse->counterpart = add_task->counterpart;
					add(traverse);
					return;
				}
				else {
					pretraverse->counterpart = add_task;
					add_task->counterpart = traverse->counterpart;
					add_task->next = NULL;
					add_task->previous = NULL;
					checkAvailableNextTimesFor(add_task);
					add_task->time = usable_time;
					add_task->day = usable_day;
					pretraverse->counterpart = traverse;
					traverse->counterpart = add_task->counterpart;
					add(add_task);
					return;
				}
			}
		}
		if(add_task->time < traverse->time){
			add_task->counterpart = traverse;
			pretraverse->counterpart = add_task;
			add_task->next = NULL;
			add_task-> previous = NULL;
			return;
		}
	}
	if(add_task->day < traverse->day){
		add_task->next = traverse;
		add_task->previous = traverse->previous;
		(traverse->previous)->next = add_task;
		traverse->previous = add_task;
	}
}
Task * WorkPlan::getTask(int day, int time)
{
	Task* iter;
	iter = head;
	while(iter && iter->day != day){
		iter = iter->next;
	}
	while (iter && iter->time != time) {
		iter = iter->counterpart;
	}
	if(iter){
		return iter;
	}
	else {
		cout << "Check your inputs" << endl;
		return NULL;
	}
}


void WorkPlan::checkAvailableNextTimesFor(Task* delayed)
{
	Task* bir, * iki,*dokuz;
	bir=head;
	iki=head;
	dokuz = head;
	while(delayed->day != bir->day){
			bir = bir->next;
			iki = iki->next;
			dokuz = iki;
		}
	int a = 0;
	while (iki) {
		dokuz = iki;
		iki = iki->counterpart;
	}
	a = dokuz->time;
	iki = bir;
	if (delayed->time < bir->time) {
		usable_day = delayed->day;
		usable_time = delayed->time;
		return;
	}
	while (delayed->time != iki->time) {
		iki = iki->counterpart;
	}
	while (delayed->time < a && delayed->time == iki->time) {
		delayed->time++;
		iki = iki->counterpart;
		if (!iki) {
			break;
		}
	}
	if (!iki && delayed->time < a) {
		usable_day = delayed->day;
		usable_time = delayed->time;
		return;
	}
	if (iki && delayed->time < a ) {
		usable_day = delayed->day;
		usable_time = delayed->time;
		return;
	}
	if (delayed->time >= a) {
		if(bir->day < bir->next->day){
			delayed->day = bir->next->day;
			delayed->time = 8;
			checkAvailableNextTimesFor(delayed);
			return;
		}
		else{
			usable_day = delayed->day ++;
			delayed->time = 8;
			usable_time = delayed->time;
		}

	}
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	Task* bir, * iki;
	Task* add2 = new Task;
	bir = head;
	iki = head;
	while (bir->day != day) {
		bir = bir->next;
		iki = iki->next;
	}
	if (bir->counterpart) {
		while (bir) {
			int a = 0;
			if (bir->next->day > bir->day) {
				a = bir->next->day;
			}
			else if (bir->next->day < bir->day) {
				a = bir->day;
				a++;
			}
			add2->day = a;
			add2->priority = bir->priority;
			add2->time = 8;
			int l = strlen(bir->name);
			add2->name = new char[l + 1];
			add2->name[l] = '\0';
			for (int i = 0; i < l; i++) {
				add2->name[i] = bir->name[i];
			}
			iki = bir->counterpart;
			remove(bir);
			checkAvailableNextTimesFor(add2);
			add2->time = usable_time;
			add2->day = usable_day;
			add(add2);
			bir = iki;
		}
	}
	else {
		int a = 0;
		if (bir->next->day > bir->day) {
			a = bir->next->day;
		}
		else if (bir->next->day < bir->day) {
			a = bir->day;
			a++;
		}
		add2->day =a;
		add2->priority = bir->priority;
		add2->time = 8;
		int l = strlen(bir->name);
		add2->name = new char[l + 1];
		add2->name[l] = '\0';
		for (int i = 0; i < l; i++) {
			add2->name[i] = bir->name[i];
		}
		remove(bir);
		checkAvailableNextTimesFor(add2);
		add2->time = usable_time;
		add2->day = usable_day;
		add(add2);
		return;
	}
}


void WorkPlan::remove(Task* target)
{
	Task* oter, * iter;
	iter = head;
	oter = head;
	while (iter->day != target->day) {
		iter = iter->next;
		oter = oter->next;
	}
	if (iter->time == target->time) {
		if (iter->time == head->time && iter->day == head->day) {
			if (iter->counterpart) {
				oter = iter->counterpart;
				(iter->next)->previous = oter;
				(iter->previous)->next = oter;
				oter->next = iter->next;
				oter->previous = iter->previous;
				iter->next = NULL;
				iter->previous = NULL;
				iter->counterpart = NULL;
				delete iter;
				head = oter;
				return;
			}
			else {
				if (head->next) {
					head = head->next;
					(iter->previous)->next = iter->next;
					(iter->next)->previous = iter->previous;
					iter->next = NULL;
					iter->previous = NULL;
					return;
				}
				else {
					head = NULL;
				}
			}
		}
		if (iter->counterpart) {
			oter = iter->counterpart;
			(iter->next)->previous = oter;
			(iter->previous)->next = oter;
			oter->next = iter->next;
			oter->previous = iter->previous;
			iter->next = NULL;
			iter->previous = NULL;
			iter->counterpart = NULL;
			delete iter;
			return;
			}
		else {
			(iter->previous)->next = iter->next;
			(iter->next)->previous = iter->previous;
			iter->next = NULL;
			iter->previous = NULL;
			delete iter;
			return;
		}
	}
	while (iter->time != target->time) {
		oter = iter;
		iter = iter->counterpart;
	}
	if (iter->counterpart) {
		oter->counterpart = iter->counterpart;
		iter->counterpart = NULL;
	}
	else {
		oter->counterpart = NULL;
	}
	delete iter;
}

bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}
