/*Deterministic Finite Automaton Minimization*/
#include <bits/stdc++.h>
using namespace std;
const int C = 109;

int t[C][C]; // transition table
bool fs[C]; // final states
bool printed[C];
vector<vector<int> > se[2]; // set of equivalence classes

// n is no of states, m is no of input symbols, nfs is no of final states
int n, m, nfs;

// Returns the index of the equivalence class containing x in se[0]
int idx(int x) {
	for(int i=0; i<se[0].size(); i++) {
		for(int j=0; j<se[0][i].size(); j++) {
			if(se[0][i][j] == x) return i;
		}
	}
}
// This Prints the minimised DFA
void print_minimum() {
    cout << "\n The Minimized DFA Table:\n";
    cout << "---------------------\n";
    cout << "Q\t";
    for(int j=0; j<m; j++) cout << j << "\t"; cout << endl << endl;
    for(int i=0; i<n; i++) {
        if(printed[i] == 1) continue;
        int ind = idx(i);
        cout << "[";
        for(int k=0; k<se[0][ind].size(); k++) {
            cout << se[0][ind][k];
            printed[k] = 1;
        }
        cout << "]\t";
        for(int j=0; j<m; j++) { 
            ind = idx(t[i][j]);
            cout << "[";
            for(int k=0; k<se[0][ind].size(); k++) {
                cout << se[0][ind][k];
            }
            cout << "]\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){

    n = 5, m = 2;
    nfs = 1; // only one final state
    // mark all the final states:
    fs[4] = 1;

    // Input transition tables:
    for(int i=0; i<n; i++) {
    	for(int j=0; j<m; j++) {
    		cin >> t[i][j];
    	}
    }

    // Initialize the set of equivalence classes
    vector<int> v[2];
    for(int i=0; i<n; i++) {
    	v[fs[i]].push_back(i);
    }
    se[0].push_back(v[0]); se[0].push_back(v[1]);
    se[1] = se[0];

    // maximum iterations
    int iter = 100;
    // Decompose the equivalence classes till old and new se are not equal
    while(iter--) {
    	se[0] = se[1];
        // se[1] is the new set, se[0] is the old set

    	for(int i=0; i<se[1].size(); i++) {
    		for(int j=1; j<se[1][i].size(); j++) {
                // find the correct equivalence class for se[1][i][j]
    			bool placed = 0;
    			for(int k=0; k<j; k++) {
    				// check se[1][i][j] with se[1][i][k]
    				bool compat = 1;
    				for(int l=0; l<m; l++) {
    					if(idx(t[se[1][i][j]][l]) != idx(t[se[1][i][k]][l])) {
                            compat = 0;
                            break;
                        }
    				}
    				if(compat) {
    					// se[1][i][j] can remain in same place
    					placed = 1;
    					break;
    				}
    			}
    			if(placed) continue;
    			for(int x = se[0].size(); x<se[1].size(); x++) {
	    			for(int k=0; k<se[1][x].size(); k++) {
	    				// check se[1][i][j] with se[1][x][k]
	    				bool compat = 1;
	    				for(int l=0; l<m; l++) {
	    					if(idx(t[se[1][i][j]][l]) != idx(t[se[1][x][k]][l])) {
                                compat = 0;
                                break;
                            }
	    				}
	    				if(compat) {
	    					// remove se[1][i][j] from se[1][i], insert in se[1][x]
	    					se[1][x].push_back(se[1][i][j]);
	    					se[1][i].erase(se[1][i].begin() + j);
	    					placed = 1;
	    					break;
	    				}
	    			}
	    			if(placed) break;
    			}
    			if(placed) continue;
    			// create new set {se[1][i][j]} and insert at end of se[1]
    			vector<int> vv; vv.push_back(se[1][i][j]);
    			se[1].push_back(vv); se[1][i].erase(se[1][i].begin() + j);
    		}
    	}
    	// compare se[0] and se[1]
    	for(int i=0; i<se[0].size(); i++) {
    		sort(se[0][i].begin(), se[0][i].end());
    	}
    	sort(se[0].begin(), se[0].end());
    	for(int i=0; i<se[1].size(); i++) {
    		sort(se[1][i].begin(), se[1][i].end());
    	}
    	sort(se[1].begin(), se[1].end());
    	if(se[0] == se[1]) break;
    }

    assert(se[0] == se[1]);

    print_minimum();

    return 0; 
} 
  
