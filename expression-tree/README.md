# Expression Evaluation

Expression evaluation is a problem of building the correct expression tree.

The use of a queue here is completely uncalled for. That said, multiple queues can be used to evaluate an expression one for operators and the other for operands but keeping the order of operands will be a bit tricky, another approach is to use stacks (which is the standard way of doing expression evaluation) that way there will be no need to worry about order of operands.

This was a project I did for my postgraduate Data Structures and Algorithms course.

["Fix" Reference](http://www.cs.man.ac.uk/~pjj/cs212/fix.html)


![](exp-eval.png?raw=true "algorithm")

_We do this to save the ~~earth~~ brackets_