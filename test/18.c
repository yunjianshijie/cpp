/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */

int candidatesSize_tmp;//
int ansSize;
int combineSize;
int* ansColumnSize;

void dfs(int * candidates,int target ,int ** ans ,int * combine ,int idx){//在 candidates 数值中idx位 
    if(idx==candidatesSize_tmp){//如果在最后扫完了就当弄完了
        return;
    }
    if(target==0 ){
        int * tmp = malloc(sizeof(int)* combineSize);
        for(int i=0;i< combineSize;i++){
            tmp[i]=combine[i];
        }
        ans[ansSize]=tmp;
        ansColumnSize[ansSize++]=combineSize;
        return;
    }
    //<=0 都过
    dfs(candidates,target,ans,combine,idx+1);
    if(target -[i candidatesdx] >= 0){
        combine[columnSizes++]=candidates[idx];
        dfs(candidates,target - candidates[idx],ans,combine,idx);
        columnSizes--;
    }
}