/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:29:56 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/22 15:40:22 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to add a node to the list
void addNode(struct Node** head, int value) {
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // If the list is empty, make the new node the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // If the new node should be inserted at the beginning
    if (value < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // Traverse the list to find the appropriate position to insert the new node
    struct Node* current = *head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }

    // Insert the new node in the middle or at the end
    newNode->next = current->next;
    current->next = newNode;
}

// Function to print the linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Test the implementation
int main() {
    // Create an empty linked list
    struct Node* head = NULL;

    // Add nodes to the list
    addNode(&head, 2);   // New node added at the beginning
    addNode(&head, 5);   // New node added at the end
    addNode(&head, 3);   // New node added in the middle
    addNode(&head, 1);   // New node added at the beginning
    addNode(&head, 4);   // New node added in the middle

    // Print the linked list
    printList(head);

    return 0;
}