library(ggplot2)
library(reshape2)  
library(ggsignif)  
df = read.delim("https://www.bioladder.cn/shiny/zyp/bioladder2/demoData/BoxPlot/boxplot.txt",header = T    
)
df = melt(df)

ggplot(df,aes(x=variable,y=value,fill=variable))+
  geom_boxplot(alpha = 1,              
               outlier.color = "black" 
  )+
  theme_bw()+                          
  theme(
    axis.text.x = element_text(angle = 90,
                               vjust = 0.5
    )       
  )+
  geom_signif(                         
    comparisons=list(c("Sample1","Sample2"),c("Sample3","Sample4")), 
    step_increase = 0.1,
    test="t.test",                     
    map_signif_level=F                 
  )