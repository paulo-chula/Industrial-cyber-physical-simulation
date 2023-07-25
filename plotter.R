pdf("results.pdf")
data <- read.table(file = 'results.txt',sep = '\t',header = TRUE,stringsAsFactors = FALSE, row.names=NULL) 
boxplot(data, main = "Sum execution time", xlab = "Number of concurrent systems", ylab = "Execution time")
dev.off()