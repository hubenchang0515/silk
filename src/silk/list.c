#include "list.h"
#include "log.h"

#include <string.h>

struct SilkList
{
    size_t element_size;
    silk_list_node_t head;
    silk_list_node_t tail;
    size_t length;
};

struct SilkListNode
{
    silk_list_t list;
    void* data;
    silk_list_node_t prev;
    silk_list_node_t next;
};

/*******************************************************
 * @brief create the first node of list
 * @param list the list
 * @param data the element data
 * @return the node
 *******************************************************/
static silk_list_node_t silk_list_make_first_node(silk_list_t list, const void* data)
{
    silk_list_node_t new_node = silk_alloc(sizeof(struct SilkListNode));
    SILK_ASSERT(new_node != NULL);

    new_node->data = silk_alloc(list->element_size);
    SILK_ASSERT(new_node->data);
    new_node->list = list;
    new_node->next = NULL;
    new_node->prev = NULL;
    silk_copy(new_node->data, data, list->element_size);
    list->head = new_node;
    list->tail = new_node;
    list->length = 1;
    return new_node;
}

/*******************************************************
 * @brief create a list
 * @param element_size the size of an element
 * @return the list
 *******************************************************/
silk_list_t silk_list_new(size_t element_size)
{
    silk_list_t list = silk_alloc(sizeof(struct SilkList));
    SILK_ASSERT(list != NULL);

    list->element_size = element_size;
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

/*******************************************************
 * @brief delete a list
 * @param list the list
 *******************************************************/
void silk_list_delete(silk_list_t list)
{
    SILK_ASSERT(list != NULL);
    silk_list_clear(list);
    silk_free(list);
}

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
void silk_list_clear(silk_list_t list)
{
    SILK_ASSERT(list != NULL);

    silk_list_node_t node = list->head;
    while (node != NULL)
    {
        silk_list_node_t next = node->next;
        silk_free(node->data);
        silk_free(node);
        node = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

/*******************************************************
 * @brief copy a list
 * @param list the list to be copied
 * @return the copied list 
 *******************************************************/
silk_list_t silk_list_copy(silk_list_t list)
{
    SILK_ASSERT(list != NULL);

    silk_list_t new_list = silk_list_new(list->element_size);
    for (silk_list_node_t node = list->head; node != NULL; node = node->next)
    {
        silk_list_push_back(new_list, node->data);
    }

    return new_list;
}

/*******************************************************
 * @brief get the element size of a list
 * @param list the list
 * @return the element size
 *******************************************************/
size_t silk_list_element_size(silk_list_t list)
{
    SILK_ASSERT(list != NULL);

    return list->element_size;
}

/*******************************************************
 * @brief get the length of a list
 * @param list the list
 * @return the length
 *******************************************************/
size_t silk_list_length(silk_list_t list)
{
    SILK_ASSERT(list != NULL);

    return list->length;
}

/*******************************************************
 * @brief get the head node of a list
 * @param list the list
 * @return the head node
 *******************************************************/
silk_list_node_t silk_list_head(silk_list_t list)
{
    return list->head;
}

/*******************************************************
 * @brief get the tail node of a list
 * @param list the list
 * @return the tail node
 *******************************************************/
silk_list_node_t silk_list_tail(silk_list_t list)
{
    return list->tail;
}

/*******************************************************
 * @brief get the prev node
 * @param node the list
 * @return the prev node
 *******************************************************/
silk_list_node_t silk_list_prev(silk_list_node_t node)
{
    return node->prev;
}

/*******************************************************
 * @brief get the next node
 * @param node the list
 * @return the next node
 *******************************************************/
silk_list_node_t silk_list_next(silk_list_node_t node)
{
    return node->next;
}

/*******************************************************
 * @brief insert an element before a node
 * @param node the node
 * @param data the element data
 * @return the new node
 *******************************************************/
silk_list_node_t silk_list_insert_before(silk_list_node_t node, const void* data)
{
    SILK_ASSERT(node != NULL);
    SILK_ASSERT(node->list != NULL);
    SILK_ASSERT(data != NULL);

    silk_list_node_t new_node = silk_alloc(sizeof(struct SilkListNode));
    SILK_ASSERT(new_node != NULL);

    new_node->data = silk_alloc(node->list->element_size);
    SILK_ASSERT(new_node->data);
    new_node->list = node->list;
    new_node->next = node;
    new_node->prev = node->prev;
    
    if (node->prev != NULL)
        node->prev->next = new_node;
    else
        node->list->head = new_node;
    node->list->length += 1;
    node->prev = new_node;
    silk_copy(new_node->data, data, node->list->element_size);
    return new_node;
}

/*******************************************************
 * @brief insert an element after a node
 * @param node the node
 * @param data the element data
 * @return the new node
 *******************************************************/
silk_list_node_t silk_list_insert_after(silk_list_node_t node, const void* data)
{
    SILK_ASSERT(node != NULL);
    SILK_ASSERT(node->list != NULL);
    SILK_ASSERT(data != NULL);

    silk_list_node_t new_node = silk_alloc(sizeof(struct SilkListNode));
    SILK_ASSERT(new_node != NULL);

    new_node->data = silk_alloc(node->list->element_size);
    SILK_ASSERT(new_node->data);
    new_node->list = node->list;
    new_node->next = node->next;
    new_node->prev = node;

    if (node->next != NULL)
        node->next->prev = new_node;
    else
        node->list->tail = new_node;
    node->list->length += 1;
    node->next = new_node;
    silk_copy(new_node->data, data, node->list->element_size);
    return new_node;
}

/*******************************************************
 * @brief remove a list node
 * @param node the node
 * @return whether it is successful
 *******************************************************/
bool silk_list_remove(silk_list_node_t node)
{
    SILK_ASSERT(node != NULL);
    SILK_ASSERT(node->list != NULL);

    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        node->list->head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;
    else
        node->list->tail = node->prev;

    node->list->length -= 1;
    silk_free(node->data);
    silk_free(node);
    return true;
}

/*******************************************************
 * @brief set a list node data
 * @param node the node
 * @param data the data
 * @return whether it is successful
 *******************************************************/
bool silk_list_set(silk_list_node_t node, const void* data)
{
    SILK_ASSERT(node != NULL);
    SILK_ASSERT(data != NULL);
    SILK_ASSERT(node->list != NULL);

    silk_copy(node->data, data, node->list->element_size);
    return true;
}

/*******************************************************
 * @brief get a list node data
 * @param node the node
 * @param data the data
 * @return whether it is successful
 *******************************************************/
bool silk_list_get(silk_list_node_t node, void* data)
{
    SILK_ASSERT(node != NULL);
    SILK_ASSERT(data != NULL);
    SILK_ASSERT(node->list != NULL);

    silk_copy(data, node->data, node->list->element_size);
    return true;
}

/*******************************************************
 * @brief get a list node
 * @param list the list
 * @param index the index
 * @return the node
 *******************************************************/
silk_list_node_t silk_list_at(silk_list_t list, size_t index)
{
    silk_list_node_t node = list->head;
    for (size_t i = 0; i < index; i++)
    {
        SILK_ASSERT(node != NULL);
        node = node->next;
    }

    return node;
}

/*******************************************************
 * @brief get a list node by backward index
 * @param list the list
 * @param index the backward index
 * @return the node
 *******************************************************/
silk_list_node_t silk_list_at_backward(silk_list_t list, size_t index)
{
    silk_list_node_t node = list->tail;
    for (size_t i = 0; i < index; i++)
    {
        SILK_ASSERT(node != NULL);
        node = node->prev;
    }

    return node;
}

/*******************************************************
 * @brief push an element to the front of a list
 * @param node the node
 * @param data the element data
 * @return the new node
 *******************************************************/
silk_list_node_t silk_list_push_front(silk_list_t list, const void* data)
{
    SILK_ASSERT(list != NULL);
    SILK_ASSERT(data != NULL);

    if (list->head != NULL)
        return silk_list_insert_before(list->head, data);
    else 
        return silk_list_make_first_node(list, data);
}

/*******************************************************
 * @brief push an element to the back of a list
 * @param node the node
 * @param data the element data
 * @return the new node
 *******************************************************/
silk_list_node_t silk_list_push_back(silk_list_t list, const void* data)
{
    SILK_ASSERT(list != NULL);
    SILK_ASSERT(data != NULL);

    if (list->tail != NULL)
        return silk_list_insert_after(list->tail, data);
    else 
        return silk_list_make_first_node(list, data);
}

/*******************************************************
 * @brief pop an element from the front of a list
 * @param node the node
 * @param data the element data
 * @return the new head node
 *******************************************************/
silk_list_node_t silk_list_pop_front(silk_list_t list, void* data)
{
    SILK_ASSERT(list != NULL);
    SILK_ASSERT(data != NULL);
    SILK_ASSERT(list->head != NULL);

    silk_list_get(list->head, data);
    silk_list_remove(list->head);
    return list->head;
}

/*******************************************************
 * @brief pop an element from the back of a list
 * @param node the node
 * @param data the element data
 * @return the new tail node
 *******************************************************/
silk_list_node_t silk_list_pop_back(silk_list_t list, void* data)
{
    SILK_ASSERT(list != NULL);
    SILK_ASSERT(data != NULL);
    SILK_ASSERT(list->tail != NULL);

    silk_list_get(list->tail, data);
    silk_list_remove(list->tail);
    return list->tail;
}

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
int silk_list_default_compare(const void* x, const void* y, const void* userdata)
{
    SILK_ASSERT(x != NULL);
    SILK_ASSERT(y != NULL);
    SILK_ASSERT(userdata != NULL);

    const silk_list_t list = (const silk_list_t)(userdata);
    return memcmp(x, y, list->element_size);
}

/*******************************************************
 * @brief find an element from the list
 * @param begin the begin node
 * @param data the element data
 * @param compare function to compare
 * @return the node
 *******************************************************/
silk_list_node_t silk_list_find(silk_list_node_t begin, const void* data, silk_compare_t compare)
{
    SILK_ASSERT(begin != NULL);
    SILK_ASSERT(data != NULL);
    SILK_ASSERT(compare != NULL);

    for (silk_list_node_t node = begin; node != NULL; node = node->next)
    {
        if (compare(node->data, data, begin->list) == 0)
            return node;
    }

    return NULL;
}

/*******************************************************
 * @brief sort a list by quick sort algorithm 
 *        with stack rather than recursion
 * @param list the list
 * @param compare function to compare
 *******************************************************/
void silk_list_sort(silk_list_t list, silk_compare_t compare)
{
    SILK_ASSERT(list != NULL);
    SILK_ASSERT(compare != NULL);

    if (list->length <= 1)
        return;

    silk_list_t stack = silk_list_new(sizeof(silk_list_node_t));
    SILK_ASSERT(stack != NULL);
    void* buffer = silk_alloc(list->element_size);
    SILK_ASSERT(buffer != NULL);

    silk_list_node_t begin = list->head;
    silk_list_node_t end = list->tail;
    SILK_ASSERT(silk_list_push_back(stack, &begin) != NULL);
    SILK_ASSERT(silk_list_push_back(stack, &end) != NULL);

    while (stack->length > 0)
    {
        silk_list_pop_back(stack, &end);
        silk_list_pop_back(stack, &begin);
        
        silk_list_node_t base = begin;
        silk_list_node_t left = begin;
        silk_list_node_t right = end;
        while (left != right)
        {
            // find right smaller than base
            for (; right != left; right = silk_list_prev(right))
            {
                if (compare(right->data, base->data, list) < 0)
                {
                    break;
                }
            }

            // find left greater than base
            for (; left != right; left = silk_list_next(left))
            {
                if (compare(left->data, base->data, list) > 0)
                {
                    break;
                }
            }

            if (left == right)
                break;

            // swap right and left
            silk_copy(buffer, left->data, list->element_size);
            silk_copy(left->data,  right->data, list->element_size);
            silk_copy(right->data,  buffer, list->element_size);
        }

        // swap base and meetion
        silk_copy(buffer, left->data, list->element_size);
        silk_copy(left->data, base->data, list->element_size);
        silk_copy(base->data,  buffer, list->element_size);

        // push the range of next turn 
        if (left != begin)
        {
            silk_list_node_t border = silk_list_prev(left);
            silk_list_push_back(stack, &begin);
            silk_list_push_back(stack, &border);
        }
        if (left != end)
        {
            silk_list_node_t border = silk_list_next(left);
            silk_list_push_back(stack, &border);
            silk_list_push_back(stack, &end);
        }
    }

    silk_free(buffer);
    silk_list_delete(stack);
}