#ifndef SILK_LIST_H
#define SILK_LIST_H

#include "common.h"
#include "compare.h"
#include "memory.h"

typedef struct SilkList* silk_list_t;
typedef struct SilkListNode* silk_list_node_t;

/*******************************************************
 * @brief create a list
 * @param element_size the size of an element
 * @return the list
 *******************************************************/
silk_list_t silk_list_new(size_t element_size);

/*******************************************************
 * @brief delete a list
 * @return the list
 *******************************************************/
void silk_list_delete(silk_list_t list);

/*******************************************************
 * @brief clear a list
 * @return the list
 *******************************************************/
void silk_list_clear(silk_list_t list);

/*******************************************************
 * @brief copy a list
 * @param list the list to be copied
 * @return the copied list 
 *******************************************************/
silk_list_t silk_list_copy(silk_list_t list);

/*******************************************************
 * @brief get the element size of a list
 * @param list the list
 * @return the element size
 *******************************************************/
size_t silk_list_element_size(silk_list_t list);

/*******************************************************
 * @brief get the length of a list
 * @param list the list
 * @return the length
 *******************************************************/
size_t silk_list_length(silk_list_t list);

/*******************************************************
 * @brief get the head node of a list
 * @param list the list
 * @return the head node
 *******************************************************/
silk_list_node_t silk_list_head(silk_list_t list);

/*******************************************************
 * @brief get the tail node of a list
 * @param list the list
 * @return the tail node
 *******************************************************/
silk_list_node_t silk_list_tail(silk_list_t list);

/*******************************************************
 * @brief get the prev node
 * @param node the list
 * @return the prev node
 *******************************************************/
silk_list_node_t silk_list_prev(silk_list_node_t node);

/*******************************************************
 * @brief get the next node
 * @param node the list
 * @return the next node
 *******************************************************/
silk_list_node_t silk_list_next(silk_list_node_t node);

/*******************************************************
 * @brief insert an element before a node
 * @param node the node
 * @param data the element data
 * @return the new node, NULL means failed
 *******************************************************/
silk_list_node_t silk_list_insert_before(silk_list_node_t node, const void* data);

/*******************************************************
 * @brief insert an element after a node
 * @param node the node
 * @param data the element data
 * @return the new node, NULL means failed
 *******************************************************/
silk_list_node_t silk_list_insert_after(silk_list_node_t node, const void* data);

/*******************************************************
 * @brief remove a list node
 * @param node the node
 * @return whether it is successful
 *******************************************************/
bool silk_list_remove(silk_list_node_t node);

/*******************************************************
 * @brief set a list node data
 * @param node the node
 * @param data the data
 * @return whether it is successful
 *******************************************************/
bool silk_list_set(silk_list_node_t node, const void* data);

/*******************************************************
 * @brief get a list node data
 * @param node the node
 * @param data the data
 * @return whether it is successful
 *******************************************************/
bool silk_list_get(silk_list_node_t node, void* data);

/*******************************************************
 * @brief get a list node by index
 * @param list the list
 * @param index the index
 * @return the node
 *******************************************************/
silk_list_node_t silk_list_at(silk_list_t list, size_t index);

/*******************************************************
 * @brief get a list node by backward index
 * @param list the list
 * @param index the backward index
 * @return the node
 *******************************************************/
silk_list_node_t silk_list_at_backward(silk_list_t list, size_t index);

/*******************************************************
 * @brief push an element to the front of a list
 * @param node the node
 * @param data the element data
 * @return the new node, NULL means failed
 *******************************************************/
silk_list_node_t silk_list_push_front(silk_list_t list, const void* data);

/*******************************************************
 * @brief push an element to the back of a list
 * @param node the node
 * @param data the element data
 * @return the new node, NULL means failed
 *******************************************************/
silk_list_node_t silk_list_push_back(silk_list_t list, const void* data);

/*******************************************************
 * @brief pop an element from the front of a list
 * @param node the node
 * @param data the element data
 * @return the new head node, NULL means empty
 * @note pop the only one node or failed both return NULL
 *******************************************************/
silk_list_node_t silk_list_pop_front(silk_list_t list, void* data);

/*******************************************************
 * @brief pop an element from the back of a list
 * @param node the node
 * @param data the element data
 * @return the new tail node, NULL means empty
 * @note pop the only one node or failed both return NULL
 *******************************************************/
silk_list_node_t silk_list_pop_back(silk_list_t list, void* data);

/*******************************************************
 * @brief default compare function with memcpy
 * @note  this function compare byte by byte
 *        so it can be used to determine if value is equal, 
 *        but it cannot compare the values of those type
 *        like little-endian int, float and double
 * @param x a value to compare
 * @param y a value to compare
 * @param userdata the list
 * @return negative value while x < y
 *         positive value while x > y
 *         0 while x == y
 *******************************************************/
int silk_list_default_compare(const void* x, const void* y, const void* userdata);

/*******************************************************
 * @brief find an element from the list
 * @param begin the begin node
 * @param data the element data
 * @param compare function to compare
 * @return the node
 *******************************************************/
silk_list_node_t silk_list_find(silk_list_node_t list, const void* data, silk_compare_t compare);

/*******************************************************
 * @brief sort a list by quick sort algorithm 
 *        with stack rather than recursion
 * @param list the list
 * @param compare function to compare
 * @return whether it is successful
 *******************************************************/
bool silk_list_sort(silk_list_t list, silk_compare_t compare);

#endif // SILK_LIST_H