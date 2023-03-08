deque<int> q;

// min
current_minimum = q.front();

//add
while (!q.empty() && q.back() > added_element)
	q.pop_back();
q.push_back (added_element);

// remove
if (!q.empty() && q.front() == removed_element)
	q.pop_front();
