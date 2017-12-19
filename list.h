#include <stddef.h>

#ifndef _LIST_H_
#define _LIST_H_

struct list_head{
  struct list_head *next, *prev;
};

void init_list_head(struct list_head *head)  //头结点
{
  head->next = head;
  head->prev = head;
}

static inline int list_empty(struct list_head *head)
{
  return head->next == head;
}

void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)  //一般插入，将new结点插入在prev和next之间
{
  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;
}

void list_add(struct list_head *new, struct list_head *head) //在链表头插入
{
  __list_add(new, head, head->next);
}
void list_add_tail(struct list_head *new, struct list_head *head)  //在链表尾插入
{
  __list_add(new, head->prev, head);
}

void list_del(struct list_head *entry)
{
  struct list_head *entry_next = entry->next;
  struct list_head *entry_prev = entry->prev;

  entry_next->prev = entry_prev;
  entry_prev->next = entry_next;
}

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:           the pointer to the member
 * @type:         the type of the container struct this embedded in
 * @member:   the name of the member within the struct
 *
 */
#define container_of(ptr, type, member) \
  ({	\
  const typeof( ((type *)0)->member  )* __mptr = (ptr);	\
  (type *)( (char *)__mptr - offsetof(type, member)  ); })

#define list_entry(ptr, type, member)		\
  container_of(ptr, type, member)

#define list_for_each(pos, head)		\
  for(pos = (head)->next; pos!=head; pos=pos->next)

#define list_for_each_safe(pos, n, head)				\
  for(pos = (head)->next, n = pos->next; pos!=head; pos = n, n = pos->next )

#endif
