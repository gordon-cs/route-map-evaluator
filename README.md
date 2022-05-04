# cps222-2022-p5-opokunyarko-colbert
### Attempted & Status

- Requirement 1 : Read and print data

Town and road data can be correctly read and outputed to the terminal. Passes all tests with no diff issues and correct styling. Peer programmed. 

- Requirement 2 : Shortest Paths

findShortestPath() method implemented to calculate shortest traversals and output them to the terminal. Passes all tests with no diff issues and correct stylings. Completed by Elijah Opoku-Nyarko with later revisions by Jake Colbert. 

- Requirement 3 : Upgrading

minSpan() method implemented to find ideal connections for faster traversals and output recomendations to the terminal. Passes all tests with no diff issues and correct stylings. Completed by Elijah Opoku-Nyarko with later revisions by Jake Colbert. 

- Requirement 4 : Worst-Case Analysis of Bridge Collapse

removeBridges() method implemented to find towns that would form isolated groups on bridge collapse. Passes all tests with some diff issues regarding ordering and correct stylings. Completed by Elijah Opoku-Nyarko with output revisions by Jake Colbert.

- Requirement 5 : Articulation Points

articulationPoints() method implemented to find points of the graph at which their destruction would disconnect the province graph. Does not pass tests. isAP[] array does not get modified by the recursive method and prints all zeros as it was initialized. In-Progress by Jake Colbert

### Makefile & Testing

A `make test-all` target has been implemented to return "Passed!" if no errors are caught when running other tests. On run, "--- <test name> ---" will be displayed to indicate which test was running upon crash. Any test error will likely result from differences in the project5.out file and the respective test.out file. View test.diff to see their differences. 