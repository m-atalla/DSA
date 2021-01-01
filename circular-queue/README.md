# Circular Queue

Circular queue also known as ring buffer, solves regular queue problem when dequeuing you either have to shift the entire array one index forward or move the queue front ahead one index both solutions are not optimal when attempting to re-use the queue. a circular queue attempts solve that problem by using the _modulo_ `%` operator to determine the front & rear indexes.

This helped me visualizing the proccess.
![Ring buffer](https://upload.wikimedia.org/wikipedia/commons/f/fd/Circular_Buffer_Animation.gif)

- read pointer indicates the front
- write pointer indicates the rear

---

Includes `reverse()` function which recusively reverse a circular queue by abusing the call stack properties of carrying variables on each frame dequeue till reaching the end of the queue then resolving every frame of the call stack by enqueuing back the value into the queue.

Or in other words I was too lazy to implement a stack data structure. :sweat_smile:

[reference](https://en.wikipedia.org/wiki/Circular_buffer)
