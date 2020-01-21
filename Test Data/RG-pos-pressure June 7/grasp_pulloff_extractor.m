%min max extractor

d =dir('/Users/kurtislaqua/OneDrive - University of Toronto/Programmable Pneumatics/Pneumatics/Test Data/RG-pos-pressure June 7/*.csv');


compiled_curves =[];
i=1;
j=1

l=60
count=0;
k=260;
direction=1;
for i=1:length(d)
  data=csvread(['/Users/kurtislaqua/OneDrive - University of Toronto/Programmable Pneumatics/Pneumatics/Test Data/RG-pos-pressure June 7/',d(i).name]);
   data_details=sscanf(d(i).name,'%d-%d-%d-%d-RGtest-%d-%d-%d.csv');
   compiled_curves(i,:) =[data_details(5) data_details(6) data_details(7) min(data(1:k)) min(data(k:length(data)))];
 

end


