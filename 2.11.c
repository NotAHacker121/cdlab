#include <stdio.h>

struct Node
{
	int transition[5][5];
} node[10];

// e_closure() find and store e-closures to e_arr
int e_arr[10];
int e_sub_arr[10];

int state, no_of_states_after_eclosure, j_th_state_in_eclosure, state_after_eclosure_alpha[50], p, k_th_alphabet, w, q;
int states_after_eclosure_alpha_eclosure[50];
int no_of_states_after_eclosure_alpha = 0;
int no_of_states_after_eclosure_alpha_eclosure = 0;

// contains the alphabets a,b,c......
char alphabets[10];

// map characters to an index value a-1, b-2 .....
int map(char alpha)
{

	if (alpha == 'e')
		return 0;
	int i = alpha - 96;
	return i;
}

// find e-closure of node e and store the result(indexes) in res[]
int e_closure(int state, int res[])
{
	int count = 0;
	res[count++] = state; // e closure contain itself
	for (int i = 0; i < count; i++)
	{
		state = res[i];
		for (int j = 0; j < 5; j++)
		{
			if (node[state].transition[map('e')][j] != -1)
			{ // check if there is an e transition
				res[count++] = node[state].transition[map('e')][j];
			}
		}
	}

	return count;
}

void get_transition(int state, char alpha)
{
	int i;
	for (int j = 0; j < 5; j++)
	{
		if ((i = node[state].transition[map(alpha)][j]) != -1)
		{ // check if there is the req transition
			state_after_eclosure_alpha[no_of_states_after_eclosure_alpha++] = i;
		}
	}
}

void perform(int number_of_nodes, int number_of_alphabet)
{
	for (state = 0; state < number_of_nodes; state++)
	{
		no_of_states_after_eclosure = e_closure(state, e_arr); // finding e-closure

		// finding transition for each alphabet
		for (k_th_alphabet = 0; k_th_alphabet < number_of_alphabet; k_th_alphabet++)
		{
			no_of_states_after_eclosure_alpha = 0; // count of states after alphabet transition from e-closure states
			for (j_th_state_in_eclosure = 0; j_th_state_in_eclosure < no_of_states_after_eclosure; j_th_state_in_eclosure++)
			{
				get_transition(e_arr[j_th_state_in_eclosure], alphabets[k_th_alphabet]);
			}												// finding transition of it for each alphabet
			no_of_states_after_eclosure_alpha_eclosure = 0; // count no of states after taking 2nd e-closure
			for (w = 0; w < no_of_states_after_eclosure_alpha; w++)
			{
				int b = e_closure(state_after_eclosure_alpha[w], e_sub_arr);
				for (q = 0; q < b; q++)
				{
					states_after_eclosure_alpha_eclosure[no_of_states_after_eclosure_alpha_eclosure++] = e_sub_arr[q];
				}
			}

			printf("\nState-> %d for alphabet %c >> { ", state, alphabets[k_th_alphabet]);
			int print;
			for (p = 0; p < no_of_states_after_eclosure_alpha_eclosure; p++)
			{
				print = 1;
				for (int r = p - 1; r >= 0; r--)
				{
					if (states_after_eclosure_alpha_eclosure[p] == states_after_eclosure_alpha_eclosure[r])
						print = 0;
				}
				if (print == 1)
					printf(" %d", states_after_eclosure_alpha_eclosure[p]);
			}
			printf(" } ");
		}
	}
}

int main()
{
	/*variables in main()
	 * 	INTEGERS
	 * number_of_nodes - no of nodes
	 * number_of_transitions - no of transitions
	 * number_of_alphabet - no of alphabets
	 *  -1 # indicates No transition for that input alphabet
	 * */
	int number_of_nodes, number_of_transitions, number_of_alphabet;
	int i, j;
	int state1, state2;
	char alpha;

	printf("\nEnter the no of nodes :");
	scanf("%d", &number_of_nodes);
	printf("\nEnter the no of alphabets: ");
	scanf("%d", &number_of_alphabet);
	for (i = 0; i < number_of_alphabet; i++)
		scanf(" %c", &alphabets[i]);

	for (i = 0; i < number_of_nodes; i++)
	{    
		for (j = 0; j < number_of_alphabet + 1; j++) // for initializing with no transition, number_of_alphabet+1 for including epsilon
			for (int k = 0; k < 5; k++)
				node[i].transition[j][k] = -1;
	}
	printf("\nEnter the no of transitions: ");
	scanf("%d", &number_of_transitions);
	printf("\nEnter the state table:>>\nSTATE ALPHABET STATE\n");
	for (i = 0; i < number_of_transitions; i++)
	{
		scanf("%d	%c	%d", &state1, &alpha, &state2);
		int k = 0;
		while (node[state1].transition[map(alpha)][k] != -1)
		{
			k++;
		}
		node[state1].transition[map(alpha)][k] = state2;
	}
	perform(number_of_nodes, number_of_alphabet);
	printf("\n");
}
