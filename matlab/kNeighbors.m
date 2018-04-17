%Computes the class prediction for a given point N based on k nearest
%neighbors and dataset X in table format.
%X: dataset in a table form. Observation number corresponds to row number,
    %the first n-1 columns should be numeric variable types. The last column
    %of the table needs to be a categorical variable type.
%k: number of elements which will make up the k-neighborhood
%r: the point for which we are making a classification

function[class] = kNeighbors(X,k,r)
    distances = size(X,1); % contains the distances between obs. and y
    
    %cast last column of X as categorical array
    C = categorical(X{:,4});
    
    %compute the euclidian distances between observations and new point r
    disp('Distances btween all obs. and new point:');
    for i=1:size(X,1)
       distances(i) = sqrt(sum( ( X{i,1:size(X,2)-1}-r ) .^2 ) ) ;
       disp( distances(i));
    end% for i = 1:length(X)
   
     
    %sort distances and find k nearest neighbors
    [~,I] = sort(distances);
    disp('Indices of k nearest neighbors and their class:');
    disp(I(1:k));
    kNeighborhood = C(I(1:k));
    disp(kNeighborhood');
    
    %compute the sum of each category in k-neighborhood
     [N,Categories] = histcounts(kNeighborhood);
     disp('number of occurences of classes in the k neighborhood');
     disp(N);
     disp(Categories);
     maxVals = find( N==max(N) );
     
     %if there is only one max return
     disp('predicted class of new point:');
     if length(maxVals) == 1
        class = Categories(maxVals);
     %choose one of the max values from the possible maxes.
     else
         index = randi( length(maxVals) );
         class = Categories(index);
     end %if
end %kNeighbors
