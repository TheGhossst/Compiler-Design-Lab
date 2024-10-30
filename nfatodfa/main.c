#include <stdio.h>

struct Transistions {
    int from;
    int input;
    int to;
};

struct Transistions Transistion[30];
int nfa_transition_count = 0;

struct StateSet {
    int states[30];
    int count;
};

struct StateSet dfa_states[30];
int dfa_state_count = 0;

int start_state = 0;
int final_state;
int dfa_final_states[30];
int dfa_final_count = 0;

int dfa_transition_table[30][2];

// Function to check if a state exists in a state set
int isset(struct StateSet *set, int state) {
    for (int i = 0; i < set->count; i++) {
        if (state == set->states[i]) return 1;
    }
    return 0;
}

// Function to add a state to a state set
void addStatetoSet(struct StateSet *set, int state) {
    if (!isset(set, state)) {
        set->states[set->count++] = state;
    }
}

// Function to get reachable states from a given state on input
struct StateSet getReachableStates(struct StateSet state, int input) {
    struct StateSet result;
    result.count = 0;

    for (int i = 0; i < state.count; i++) {
        int current_state = state.states[i];
        for (int j = 0; j < nfa_transition_count; j++) {
            if (Transistion[j].from == current_state && Transistion[j].input == input) {
                addStatetoSet(&result, Transistion[j].to);
            }
        }
    }
    return result;
}

// Function to find index of a state in DFA state set
int findIndex(struct StateSet state) {
    for (int i = 0; i < dfa_state_count; i++) {
        if (state.count == dfa_states[i].count) {
            int match = 1;
            for (int j = 0; j < state.count; j++) {
                if (state.states[j] != dfa_states[i].states[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) return i;
        }
    }
    return -1;
}

// Function to add a state to DFA states
int addState(struct StateSet state) {
    int index = findIndex(state);
    if (index == -1) {
        dfa_states[dfa_state_count] = state;
        index = dfa_state_count;
        if (isset(&state, final_state)) {
            dfa_final_states[dfa_final_count++] = index;
        }
        dfa_state_count++;
    }
    return index;
}


// Conversion function for NFA to DFA
void conversion() {
    struct StateSet initial_state_set;
    initial_state_set.count = 1;
    initial_state_set.states[0] = start_state;

    addState(initial_state_set);

    for (int i = 0; i < dfa_state_count; i++) {
        for (int j = 0; j < 2; j++) {
            struct StateSet reachable = getReachableStates(dfa_states[i], j);
            int target_index = addState(reachable);
            dfa_transition_table[i][j] = target_index;
        }
    }
}

// Function to add a transition to the NFA
void addTransition(int from, int input, int to) {
    Transistion[nfa_transition_count].from = from;
    Transistion[nfa_transition_count].input = input;
    Transistion[nfa_transition_count].to = to;
    nfa_transition_count++;
}

// Function to print DFA transition table
void printDFA() {
    printf("\n\n**** NFA to DFA Conversion ****\n\n");
    printf("DFA Transition Table:\n");
    printf("State\tInput\tTransition\n");
    printf("-----------------------------\n");

    for (int i = 0; i < dfa_state_count; i++) {
        // Check if the state is a final state
        int is_final = 0;
        for (int j = 0; j < dfa_final_count; j++) {
            if (dfa_final_states[j] == i) {
                is_final = 1;
                break;
            }
        }

        // Indicate final state with '*'
        if (is_final) {
            printf("*Q%d\t0\tQ%d\n", i, dfa_transition_table[i][0]);
            printf("*Q%d\t1\tQ%d\n", i, dfa_transition_table[i][1]);
        } else {
            printf(" Q%d\t0\tQ%d\n", i, dfa_transition_table[i][0]);
            printf(" Q%d\t1\tQ%d\n", i, dfa_transition_table[i][1]);
        }
        printf("-----------------------------\n");
    }
}


// Function to verify if a string is accepted by the NFA
int verifyNFA(struct StateSet state, char *str) {
    if (*str == '\0') {
        return isset(&state, final_state);
    }

    struct StateSet reachable = getReachableStates(state, *str - '0');
    return verifyNFA(reachable, str + 1);
}

// Function to verify if a string is accepted by the DFA
int verifyDFA(char *str) {
    int current_state = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        current_state = dfa_transition_table[current_state][str[i] - '0'];
    }
    for (int i = 0; i < dfa_final_count; i++){
        if (dfa_final_states[i] == current_state){
            return 1;
        }
    }
    return 0;
}

int main() {
    int from, to, input;
    while (1) {
        if (scanf("%d", &from) != 1 || from == -1) break;
        if (scanf("%d %d", &input, &to) != 2) break;
        addTransition(from, input, to);
    }

    printf("\nEnter final state: ");
    scanf("%d", &final_state);

    conversion();
    printDFA();

    char str[30];
    printf("Enter string to verify: ");
    scanf("%s", str);

    struct StateSet initial_state_set;
    initial_state_set.count = 1;
    initial_state_set.states[0] = start_state;

    int nfa_result = verifyNFA(initial_state_set, str);
    int dfa_result = verifyDFA(str);

    printf("String is %saccepted by NFA\n", nfa_result ? "" : "not ");
    printf("String is %saccepted by DFA\n", dfa_result ? "" : "not ");

    return 0;
}