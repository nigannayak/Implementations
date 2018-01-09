// Implementation of K-Means Clustering

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void FindClusters(vector <int> dataset, int n, int k)   // Important function which will print the clusters formed
{
    sort(dataset.begin(),dataset.end());  // Sort the dataset for easier operations.

    vector <int> v;
    vector <vector <int> > datavec(k,v);
    vector <int> mean;
    vector <int> tempmean;

    int till = n/k;

    // Below is the step for calculating the first mean
    // So we have randomly selected the mid-interval values for easy operations on means
    for(int i = 0 ; i < n ; i++)
    {
        if((i+1)%till == 0)
            mean.push_back(dataset[i]);
    }

    int i(0);
    int j(0);
    
    // Below code is to calculate the clusters after forming the first mean.
    while(j < n)
    {
        int k = i;
        int diff = abs(mean[k]-dataset[j]);
        k++;

        while(k < n && diff > abs(mean[k]-dataset[j]))
        {
            diff = abs(mean[k]-dataset[j]);
            k++;
        }

        k--;
        datavec[k].push_back(dataset[j]);
        i = k;
        j++;
    }

    // Given below is the commented code to check whether i was going right till here or not ..
    /*for(i = 0 ; i < k ; i++)
    {
        cout<<mean[i]<<" :: ";
        for(j = 0 ; j < datavec[i].size() ; j++)
            cout<<datavec[i][j]<<" ";

        cout<<endl;
    }*/

    // Now we have to keep changing the mean and the clusters until we find the common mean and clusters from the previous one ...
    // Initially tempmean == empty.
    
    while(mean != tempmean)     // Here mean == new mean vector and tempmean == old mean vector generated
    {
        tempmean = mean;        // tempmean (oldmean) vector becomes equal to the new mean vector for comparison purpose.
        for(i = 0 ; i < k ; i++)
        {
            int sum(0);
            for(j = 0 ; j < datavec[i].size() ; j++)
                sum += datavec[i][j];

            mean[i] = sum/(datavec[i].size());    // new mean vector is changing now ..
        }

        vector <vector <int> > tempdatavec(k,v);

        i = 0;
        j = 0;

        // Below loop is for assigning the data values to their proper cluster where they belong.
        while(j < n)
        {
            int k = i;
            int diff = abs(mean[k]-dataset[j]);   // Finding the difference between the values and old mean vector.
            k++;

            while(k < n && diff > abs(mean[k]-dataset[j]))
            {
                diff = abs(mean[k]-dataset[j]);
                k++;
            }

            k--;
            tempdatavec[k].push_back(dataset[j]);
            i = k;
            j++;
        }

        datavec = tempdatavec;       // Assigning the value of new cluster to the old cluster.
    }

    // So we came out of the loop ... it means,, old mean vector becomes equal to the new mean vector.
    // Printing the final values of clusters with their mean values::
    cout<<"The final list::\n\n";
    for(i = 0 ; i < k ; i++)
    {
        cout<<mean[i]<<" :: ";   // Printing the mean value of the cluster first.
        for(j = 0 ; j < datavec[i].size() ; j++)    // Now printing all the data values present inside that cluster.
            cout<<datavec[i][j]<<" ";

        cout<<endl;
    }
}   // Function ends here and so our problem.

int main ()
{
    // First of all take no. of data items
    int n;
    cin>>n;

    // Now take how many clusters you want to make
    int k,x;
    cin>>k;

    // If no. of clusters are greater than the no. of elements, then it will not consider it as it will fail.
    if(k > n)
        cout<<"Such case is not possible";

    else
    {
        // Take the inputs as data
        vector <int> dataset;
        for(int i = 0 ; i < n ; i++)
        {
            cin>>x;
            dataset.push_back(x);
        }

        FindClusters(dataset,n,k);
    }

    return 0;
}