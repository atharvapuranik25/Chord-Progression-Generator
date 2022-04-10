#include <iostream>
#include <string>
#include <map>
#include <list>
#include <unistd.h>
using namespace std;

//Gives the chords from the scale based on the key input given by the user
list<string> getScale(list<string> chromatic, string key, int genre)
{
    list<string> scale;
    list<string> :: iterator it;
    for(it=chromatic.begin(); it!=chromatic.end(); it++)
    {
        if(*it == key)
        {
            if(genre==1)
            {
                scale.push_back(*it+"5");       //C
                advance(it,2);
                scale.push_back(*it+"5");       //D
                advance(it,2);
                scale.push_back(*it+"5");       //E
                advance(it,1);
                scale.push_back(*it+"5");       //F
                advance(it,2);
                scale.push_back(*it+"5");       //G
                advance(it,2);
                scale.push_back(*it+"5");       //A
                advance(it,2);
                scale.push_back(*it+"dim");     //B
            }
            else if(genre==3)
            {
                scale.push_back(*it+"7");       //C
                advance(it,2);
                scale.push_back(*it+"m");       //D
                advance(it,2);
                scale.push_back(*it+"m");       //E
                advance(it,1);
                scale.push_back(*it+"7");       //F
                advance(it,2);
                scale.push_back(*it+"7");       //G
                advance(it,2);
                scale.push_back(*it+"m");       //A
                advance(it,2);
                scale.push_back(*it+"dim");     //B
            }
            else
            {
                scale.push_back(*it);           //C
                advance(it,2);
                scale.push_back(*it+"m");       //D
                advance(it,2);
                scale.push_back(*it+"m");       //E
                advance(it,1);
                scale.push_back(*it);           //F
                advance(it,2);
                scale.push_back(*it);           //G
                advance(it,2);
                scale.push_back(*it+"m");       //A
                advance(it,2);
                scale.push_back(*it+"dim");     //B
            }
            
        }
    }
    return scale;
}

//Populates the adjacency list for a major scale chord graph
map<int,list<int>> majorGraph(map<int,list<int>> graph)
{
    graph[1].push_back(3);
    graph[1].push_back(4);
    graph[1].push_back(5);
    graph[1].push_back(6);
    graph[2].push_back(1);
    graph[2].push_back(5);
    graph[3].push_back(2);
    graph[3].push_back(4);
    graph[3].push_back(6);
    graph[4].push_back(1);
    graph[4].push_back(2);
    graph[4].push_back(5);
    graph[5].push_back(1);
    graph[5].push_back(6);
    graph[6].push_back(2);
    graph[6].push_back(4);
    return graph;
}

//Add chords to the list
list<int> addChord(int last, list<int> prog, map<int,list<int>> graph)
{
    map<int,list<int>> :: iterator it;
    srand(time(0));
    for(it = graph.begin(); it!=graph.end(); it++)
    {
        if((*it).first==last)
        {
            list<int> :: iterator iter;
            iter = (*it).second.begin();
            int random = rand() % (*it).second.size();
            advance(iter, random);
            prog.push_back(*iter);
        }
    }

    return prog;
}

//Generate a chord progression
list<int> progression(map<int,list<int>> graph, list<int> prog, int num)
{
    sleep(3);
    while(prog.size()<num)
    {
        prog = addChord(prog.back(), prog, graph);
        if(prog.size()==num)
        {
            if(prog.back() == 3)
            {
                prog.pop_back();
            }
            else if(prog.back() == 6)
            {
                prog.pop_back();
            }
        }
    }
    return prog;
}


//Prints the adjacency list of the graph
void printAdjList(map<int,list<int>> graph)
{
    cout<<"\nGraph"<<endl;
    map<int,list<int>> :: iterator it;
    for(it = graph.begin(); it!=graph.end(); it++)
    {
        cout << (*it).first << " --> ";
        list<int> :: iterator iter;
        for(iter = (*it).second.begin(); iter!=(*it).second.end(); iter++)
        {
            cout<<*iter<<" ";
        }
        cout<<endl;
    }
}

//Display the chords in the key
void display(list<string> lst)
{
    cout<<endl<<endl;
    int i=1;
    list<string> :: iterator iter;
    for(iter = lst.begin(); iter!=lst.end(); iter++)
    {
        cout<<i<<"."<<*iter<<endl;
        i++;
    }
    cout<<endl;
}

int main()
{
    map<int,list<int>> graph;
    graph = majorGraph(graph);

    cout<<"\n###########################################"<<endl;
    cout<<"\n        Chord Progression Generator"<<endl;
    cout<<"\n###########################################"<<endl;

    printAdjList(graph);

    string key;
    cout<<"\nEnter the major key: ";
    cin>>key;

    int genre;
    cout<<"\nSelect genre:"<<endl;
    cout<<"1. Rock"<<endl;
    cout<<"2. Pop"<<endl;
    cout<<"3. Blues"<<endl;
    cout<<"4. Jazz"<<endl;
    cout<<"\nGenre: ";
    cin>>genre;

    list<string> chromatic = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    list<string> scale = getScale(chromatic, key, genre);

    int num;
    cout<<"\nEnter number of chords: ";
    cin>>num;

    list<int> prog;
    if(genre==4)
    {
        prog.push_back(2);
    }
    else
    {
        prog.push_back(1);
    }

    prog = progression(graph, prog, num);

    cout<<"\nChord Progression: ";
    list<int> :: iterator iter;
    for(iter = prog.begin(); iter!=prog.end(); iter++)
    {
        cout<<*iter<<" ";
    }

    cout<<"\n\nChords in the key of "<<key<<" are:";
    display(scale);

    return 0;
}