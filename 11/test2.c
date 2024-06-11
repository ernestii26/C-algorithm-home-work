#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define MAXDEPTH 10008
#define int long long
typedef struct node {
    long long id;
    long long dis;
    struct node *up;
    struct node *down;
    long long lostNode;
    long long remain;
    long long depth;
} Node;

typedef struct queue {
    Node *head; 
    Node *tail;
    long long size;
} Queue;

typedef struct queueForOp5 {
    Node *head; 
    Node *tail;
    long long size;
} queueForOp5;

Node *genNode(long long id) {
    Node *node = (Node *)malloc(sizeof(Node));
    assert(node != NULL);
    node->id = id;
    node->up = NULL;
    node->down = NULL;
    return node;
}

Node *genNodeSpecial(long long lostNode, long long remain, long long depth) {
    Node *node = (Node *)malloc(sizeof(Node));
    assert(node != NULL);
    node->lostNode = lostNode;
    node->remain= remain;
    node->depth = depth;
    node->up = NULL;
    node->down = NULL;
    return node;
}

queueForOp5 pushQ(queueForOp5 q, long long lostNode, long long remain, long long depth){
    if(q.head == NULL){
        q.head = genNodeSpecial(lostNode, remain, depth);
        q.tail = q.head;
    }else{
        q.tail->down  = genNodeSpecial(lostNode, remain, depth);
        q.tail->down->up = q.tail;
        q.tail =  q.tail->down;
    }    
    return q;
}

queueForOp5 popHeadQ(queueForOp5 q){
    if(q.head == NULL){
        return q;
    }
    if(q.head == q.tail){
        q.head = NULL;
        q.tail = NULL;
    }else{
        q.head = q.head->down;s
        q.head->up = NULL;
    }
    return q;
}

queueForOp5 popTailQ(queueForOp5 q){
    if(q.tail == NULL){
        return q;
    }
    if(q.tail != q.head){
        q.tail = q.tail->up;
        q.tail->down = NULL;
    }else{
        q.head = NULL;
        q.tail = NULL;        
    }
    return q;
}

void functionOne(Node **current, Queue a[], long long *depth, long long distanceSum[], long long distanceToUp[], long long route[]){
    *current = a[(*current)->id].head;//id對就好
    if((*current)->down == NULL){
        printf("-1\n");
    }else {
        *current = (*current)->down;
        printf("%lld\n", (*current)->id); // Use %lld for long long
        *depth += 1;
        distanceSum[*depth] = distanceSum[*depth - 1] + distanceToUp[(*current)->id];
        route[*depth] = (*current)->id;
    }
}

void functionTwo(Node **current, Node *underParentLocation[], long long *depth) {
    if (underParentLocation[(*current)->id] == NULL) {
        printf("-1\n");
    } else {
        *current = underParentLocation[(*current)->id];
        Node *temp = *current;
        *current = temp->up;
        printf("%lld\n", (*current)->id); 
        (*depth)--;
        (*current)->down = temp->down;
        if (temp->down != NULL) {
            temp->down->up = *current; 
        }
    }
}

void dfs(Queue a[], Node *current, long long parent[], Queue monoq[], long long distanceToUp[], Queue pushedNodes[]){
    if (a[current->id].head->down == NULL){
        return;
    }
    Node *temp = a[current->id].head->down ;
    while(temp != NULL){
        dfs(a, temp, parent, monoq, distanceToUp, pushedNodes);
        long long max = 0;
        if(monoq[temp->id].head != NULL){
            max = monoq[temp->id].head->id;
        }
        max = max + distanceToUp[temp->id];
        while(monoq[current->id].tail != NULL && monoq[current->id].tail->id < max){
            //
            pushedNodes[current->id].tail = pushedNodes[current->id].tail->up;
            pushedNodes[current->id].tail->down = NULL;
            if(pushedNodes[current->id].tail == pushedNodes[current->id].head){
                pushedNodes[current->id].tail = NULL;
                pushedNodes[current->id].head->down = NULL;
            }
            //
            monoq[current->id].tail = monoq[current->id].tail->up;
            monoq[current->id].tail->down = NULL;
            if(monoq[current->id].tail == monoq[current->id].head){
                monoq[current->id].tail = NULL;
                monoq[current->id].head->down = NULL;
            }
        } 
        if(monoq[current->id].head == NULL){
            monoq[current->id].head = genNode(max);
            pushedNodes[current->id].head = genNode(temp->id);
        }else if(monoq[current->id].tail == NULL){
            if(max > monoq[current->id].head->id){
                monoq[current->id].head = genNode(max);
                pushedNodes[current->id].head = genNode(temp->id);
            }else{
                monoq[current->id].tail = genNode(max);
                monoq[current->id].head->down = monoq[current->id].tail;
                monoq[current->id].tail->up = monoq[current->id].head;

                pushedNodes[current->id].tail = genNode(temp->id);
                pushedNodes[current->id].head->down = pushedNodes[current->id].tail;
                pushedNodes[current->id].tail->up = pushedNodes[current->id].head;                
            }
        }else{
            monoq[current->id].tail->down = genNode(max);
            monoq[current->id].tail->down->up = monoq[current->id].tail;
            monoq[current->id].tail = monoq[current->id].tail->down;

            pushedNodes[current->id].tail->down = genNode(temp->id);
            pushedNodes[current->id].tail->down->up =pushedNodes[current->id].tail;
            pushedNodes[current->id].tail = pushedNodes[current->id].tail->down;
        }
        //
        temp = temp->down;
    }
}

long long operationThree(long long depth, long long distanceSum[], long long ti){
    long long left = 0;
    long long right = depth;
    long long m, ans = -1;
    while(left <= right){
        m = (left + right) / 2;
        if(distanceSum[depth] - distanceSum[m] > ti){
            ans = m;
            left = m + 1;
        }else{
            right = m - 1;
        }
    }
    return ans + 1;
}

signed main(){
    long long N;
    long long M; 
    long long Q;
    scanf("%lld%lld%lld", &N, &M, &Q);
    Queue a[N + 5];
    Queue monoq[N + 5];
    Queue pushedNodes[N + 5];
    Node *underParentLocation[N + 5];
    long long parent[N + 5];
    long long distanceToUp[N + 5];
    Queue treasureDepth;
    queueForOp5 treasure;
    for(int i = 0; i < N; i++){
        a[i].head = genNode(i);
        a[i].tail = NULL;
        a[i].size = 1;
        underParentLocation[i] = NULL;
        monoq[i].head = NULL;
        monoq[i].tail = NULL;
        pushedNodes[i].head = NULL;
        pushedNodes[i].tail = NULL;
    }
    treasure.head = NULL;
    treasure.tail = NULL;
    treasureDepth.head = NULL;
    treasureDepth.tail = NULL;
    treasure.size = 0;
    treasureDepth.size = 0;
    for(long long i = 0; i < M; i++){
        long long upNode;
        long long downNode; 
        long long distance;
        scanf("%lld%lld%lld", &upNode, &downNode, &distance);
        Node *temp = genNode(downNode);
        if(a[upNode].tail == NULL){
            a[upNode].head->down = temp;
            temp->up = a[upNode].head;
        }else{
            a[upNode].tail->down = temp;
            temp->up = a[upNode].tail;            
        }
        a[upNode].tail = temp;
        a[upNode].size += 1;
        parent[downNode] = upNode;
        underParentLocation[downNode] = temp;
        distanceToUp[downNode] = distance;
    }
    parent[0] = -1;
    dfs(a, a[0].head, parent, monoq, distanceToUp, pushedNodes);
    Node *current = a[0].head;
    long long depth = 0;
    long long distanceSum[MAXDEPTH]; //distance to 0
    long long route[MAXDEPTH]; //record every node i visit by depth
    distanceSum[0] = 0; 
    route[0] = 0;
    for(long long i = 0; i < Q; i++){
        Node *temp = treasureDepth.head;
        while(temp != NULL){
            temp = temp->down;
        }
        long long type;
        scanf("%lld", &type);
        if(type == 1){
            functionOne(&current, a, &depth, distanceSum, distanceToUp, route);
        }else if(type == 2){
            if (underParentLocation[current->id] == NULL) {
                printf("-1\n");
            } else {
                //for operation 4
                long long ttemp = current->id;
                if(parent[ttemp] != -1 && pushedNodes[parent[ttemp]].head != NULL && ttemp == pushedNodes[parent[ttemp]].head->id){
                    ttemp = parent[ttemp];
                    if(pushedNodes[ttemp].head->down != NULL){
                        pushedNodes[ttemp].head = pushedNodes[ttemp].head->down;
                        pushedNodes[ttemp].head->up = NULL;
                        monoq[ttemp].head = monoq[ttemp].head->down;
                        monoq[ttemp].head->up = NULL;
                    }else{
                        pushedNodes[ttemp].head = NULL;
                        monoq[ttemp].head = NULL;
                    }
                } 

                //poptail for operation 5
                if(treasure.tail != NULL && treasure.tail->depth == depth){
                    treasure = popTailQ(treasure);
                    if(treasure.head != NULL && treasure.tail->depth >= depth){
                        treasure.tail->depth = depth - 1;
                    }
                    treasure.size -= 1;
                }
                //

                current = underParentLocation[current->id];
                Node *temp = current;
                current = temp->up;
                printf("%lld\n", current->id); 
                depth--;
                current->down = temp->down;
                if (temp->down != NULL) {
                    temp->down->up = current; 
                }
            }
        }else if(type == 3){
            long long ti;
            scanf("%lld", &ti);
            long long left = 0;
            long long right = depth;
            long long m;
            while(left <= right){
                m = (left + right) / 2;
                if(distanceSum[depth] - distanceSum[m] > ti){
                    left = m + 1;
                }else if(distanceSum[depth] - distanceSum[m] == ti){
                    break;
                }else if(distanceSum[depth] - distanceSum[m] < ti){
                    right = m - 1;
                }
            }
            if(distanceSum[depth] - distanceSum[m] > ti){
                m = m + 1;
            }
            printf("%lld\n", route[m]);
        } else if (type == 4) {
            if(monoq[current->id].head != NULL){
                printf("%lld\n", monoq[current->id].head->id);
            }else{
                printf("0\n");
            } 
        }else if(type == 5){
            long long value;
            scanf("%lld", &value);
            long long remain = value - distanceSum[depth];
            long long lostNode = operationThree(depth, distanceSum, value);
            if(lostNode != 0)
            {
                remain = -1;
            }
            else
            {
                lostNode = remain;
                remain = 0;
            }
            treasure = pushQ(treasure, lostNode, remain, depth);
            treasure.size += 1;
            if(treasure.size > depth){
                if(treasure.head->remain == -1){
                    printf("value lost at %lld\n", route[treasure.head->lostNode - 1]);
                }else{
                    printf("value remaining is %lld\n", treasure.head->lostNode);
                }
                treasure = popHeadQ(treasure);
                treasure.size -= 1;
            }
        }
    }
}

