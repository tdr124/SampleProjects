%Power Grids with radial topologies are susceptible to many types of 
%failures. Failures may occur for any number of reasons. Examples include 
%weather related events, age related failure, distance from urban centers 
%and geographical features. ProbX calculates the probability of 
% of s users losing power over network k, with probability ofnode r failure r.


function [ P ] = probX( s, r, k )

%The value is assumed to be in bounds, as we will be checking it before
%passing to the function to allow for faster run times.

kSize = size(k.L);
eSize = size(r.E);

%Case of no power over entire random variable
if(s==0)
    p1=1;
    p2=1;
    %For each load point on the random variable
    for(i = 1:kSize(1))
        %calculate the probability of it being due to load point failures
        p1 = p1*(k.pe(i)+(1-k.pe(i))*(1-r.C(i,1)*r.C(i,2)));
        %calculate the probability of confirmed main line failures
        p2 = p2*r.C(i,1)*r.C(i,2)*(1-k.pe(i));
    end
    %Put the two together
    P = p1 + (1-r.A(1)*r.A(2))*p2;

%All other cases
else
    p=1;
    q=1;
    P=0;
    %For each combination of nodes with and without power
    for(i=1:kSize(2))
        %If that combination has the proper number of people with power
        if(k.S(i)==s)
            %Loop through all the load points
            for(j=1:kSize(1))
                %If the load point is not down
                if(k.L(j,i)~=0)
                    %Then c and d have to be working
                    q=r.C(j,1)*r.C(j,2);
                    %Loop through all of the nodes
                    for(l=1:eSize(2))
                        %Check if they are on the load point in question
                        if(r.N(j,l)~=0)
                            %Check if that one failed under the given
                            %combination
                            if(k.B(l,i)==0)
                                q=q*(1-r.E(j,l));
                            %Otherwise that one worked under the given
                            %combination
                            else
                                q=q*r.E(j,l);
                            end
                        end
                    end
                %Otherwise the load point is down, calculate the
                %probability of that.
                else
                    q=1-r.C(1)*r.C(2)*(1-k.pe(j));
                end
                %Multiply the proababilities of all the load points being
                %up or down given the combination
                p=p*q;
            end
            %Add up all the proababilities of te combinations that give the
            %proper number of custimers with power
            P=P+p;
        end
    end
    %Since for all other cases at least one person has power, the main line
    %has to be working, so multiply by the probability of that occurring. 
    P=r.A(1)*r.A(2*P;
end
end

