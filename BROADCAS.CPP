#include<stdio.h>
#include<conio.h>
#define INF 9999
#define max 10
void prims(int graph[max][max],int n)
{
	int min,x,y,i,j,edge_count=0;
	int selected[max]={0};
	selected[0]=1;
	printf("Edges in broadcast tree: \n");
	while(edge_count<n-1)
	{
		min =INF;
		for(i=0;i<n;i++)
		{
			if(selected[i])
			{
				for(j=0;j<n;j++)
				{
					if(!selected[j]&&graph[i][j]&&graph[i][j]<min)
					{
						min=graph[i][j];
						x=i;
						y=j;
					}
				}
			}
		}
		printf("%d--%d: %d\n",x,y,min);
		selected[y]=1;
		edge_count++;
	}
}
int main()
{
	int graph[max][max],n,i,j;
	printf("Enter the number of nodes:");
	scanf("%d",&n);
	printf("Enter the adjacency matrix:");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&graph[i][j]);
			if(graph[i][j]==0)
			  graph[i][j]=INF;
		}
	}
	prims(graph,n);
	getch();
	return 0;
}
