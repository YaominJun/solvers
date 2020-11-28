#include <stdio.h>
#include <dlfcn.h>
#include <cmath>
#include "ros/ros.h"
#include "ipsolve/lp_lib.h"

int main(int argc, char **argv)
{
  ros::init(argc,argv,"h_learn");
  ros::NodeHandle n; 

  lprec *lp;
  REAL row[1 + 3]; /* must be 1 more then number of columns ! */
  lp = make_lp(0,3);
  if(lp == NULL){
    fprintf(stderr, "Unable to create new LP model\n");
    return(1);
  }
  set_add_rowmode(lp, TRUE);//相当于设置开关，打开
  set_maxim(lp);//求解最大
  row[1] = 4;
  row[2] = 2;
  row[3] = 1;
  set_obj_fn(lp, row); /* construct the obj: 4 x1 + 2 x2 + x3 */

  row[1] = 2;
  row[2] = 1;
  row[3] = 0;
  add_constraint(lp, row, LE, 1);//约束1
  row[1] = 1;
  row[2] = 0;
  row[3] = 2;
  add_constraint(lp, row, LE, 2);//约束2
  row[1] = 1;
  row[2] = 1;
  row[3] = 1;
  add_constraint(lp, row, EQ, 1);//约束3
  set_bounds(lp, 1, 0.0, 1.0);//设置上下限
  set_bounds(lp, 2, 0.0, 1.0);//默认下限是0，其实可以用set_upbo
  set_bounds(lp, 3, 0.0, 2.0);
  set_add_rowmode(lp, FALSE);//开关关闭
  solve(lp);//求解
  print_solution(lp, 1);

  delete_lp(lp);

  return 0;
}
