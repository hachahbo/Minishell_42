/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:40:19 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/05 16:38:54 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  #include <libc.h>
// int main()
// {
//     char s[100];
 
//     // printing current working directory
//     printf("%s\n", getcwd(s, 100));
 
//     // using the command
//     chdir("..");
 
//     // printing current working directory
//     printf("%s\n", getcwd(s, 100));
 
//     // after chdir is executed
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>

// // Structure for a node
// struct Node {
//     int data;
//     struct Node* next;
// };

// // Function to delete a node from the middle of a linked list
// void deleteNodeFromMiddle(struct Node* node) {
//     if (node == NULL || node->next == NULL) {
//         // If the node is NULL or the next node is NULL, it cannot be deleted
//         printf("Invalid node to delete.\n");
//         return;
//     }

//     struct Node* temp = node->next;
//     node->data = temp->data;
//     node->next = temp->next;
//     free(temp);
// }

// // Function to print the linked list
// void printList(struct Node* head) {
//     struct Node* temp = head;
//     while (temp != NULL) {
//         printf("%d ", temp->data);
//         temp = temp->next;
//     }
//     printf("\n");
// }

// // Function to create a new node with given data
// struct Node* newNode(int data) {
//     struct Node* node = (struct Node*)malloc(sizeof(struct Node));
//     node->data = data;
//     node->next = NULL;
//     return node;
// }

// // Main function to test the deleteNodeFromMiddle function
// int main() {
//     struct Node* head = newNode(1);
//     head->next = newNode(2);
//     head->next->next = newNode(3);
//     head->next->next->next = newNode(4);
//     head->next->next->next->next = newNode(5);

//     printf("Original Linked List: ");
//     printList(head);

//     // Delete the node in the middle (in this case, the node with data 3)
//     deleteNodeFromMiddle(head->next->next);

//     printf("Updated Linked List: ");
//     printList(head);

//     return 0;
// }


#include <stdio.h>
#include <unistd.h>
#include <libc.h>

void cd(char *path) {
  if (chdir(path) != 0) {
    perror("chdir");
    exit(1);
  }
}

int main() {
  char path[PATH_MAX];
  printf("Enter the path to the directory you want to change to: ");
  fgets(path, PATH_MAX, stdin);
  path[strlen(path) - 1] = '\0';
  cd(path);
  printf("Changed to directory: %s\n", getcwd(NULL, 0));
  return 0;
}