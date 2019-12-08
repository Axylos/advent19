#include <point.h>
#include <op.h>
struct PointSet* build_seen_pt_set(struct OpList* ops);

void walk(struct PointSet* set, struct Point* pos, char dir, int dist);
struct Point* gen_pt_from_op(struct Point origin, struct Op op);

int find_distance_to_closest_intersection(struct PointSet* intersections);
int find_fewest_steps(struct PointSet* intersections);
