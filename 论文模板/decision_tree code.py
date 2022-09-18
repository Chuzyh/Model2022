# %%
import pandas as pd
from sklearn.tree import DecisionTreeClassifier as dtc
import numpy as np
from sklearn.tree import plot_tree
from sklearn.model_selection import RandomizedSearchCV
import seaborn as sns
import matplotlib.pyplot as plt
pd.set_option('display.max_columns',None)

# %%
df=pd.read_csv("C:/Users/Krebs/Desktop/task3_train_data.txt",header=None,sep=' ')

# %%
df_1=pd.read_csv("C:/Users/Krebs/Desktop/data/附件1测试数据",header=None,sep=' ')

# %%
train_x=df.iloc[:,1:101]
train_y=df.iloc[:,101]

# %%
param_grid={
    'min_samples_leaf':np.arange(0.05,0.75,0.05),
    'max_leaf_nodes':range(2,50,1),
    'random_state':range(0,100)
}
rs=RandomizedSearchCV(dtc(),param_grid,n_iter=1000,cv=3,scoring='f1',n_jobs=1)
# %%
rs.fit(X=train_x,y=train_y)
best_para=rs.best_params_

dt=dtc(best_para)

# %%
dt.fit(X=train_x,y=train_y)

# %%
dt.score(X=train_x,y=train_y)

# %%
df[102]=dt.predict(X=train_x)

# %%
df_1[102]=dt.predict(X=df_1.iloc[:,1:101])

# %%
df_1[102].value_counts()

# %%
tp=df[(df[101]==1) & (df[102]==1)].shape[0]
fp=df[(df[101]==0) & (df[102]==1)].shape[0]
pcs=tp/(tp+fp)
pcs

# %%
fn=df[(df[101]==1) & (df[102]==0)].shape[0]
rc=tp/(tp+fn)
fn

# %%
F1=2*pcs*rc/(pcs+rc)
F1

# %%
plt.figure(figsize=(20,20))
plot_tree(dt)
plt.title('Tree')
plt.savefig('tree.jpg')

# %%
plt.figure(figsize=(10,10))
sns.countplot(x=df[102],hue=df[101])
plt.xlabel('predict')
plt.legend(['0','1'])
plt.savefig('2.jpg')

# %%
t=pd.read_csv("C:/Users/Krebs/Desktop/data/data4_1.data",header=None,sep=' ')
ddf=pd.DataFrame(t[0])
ddf

# %%
for i in range(1,13):
    loc='C:/Users/Krebs/Desktop/data/data4_'+str(i)+'.data'
    t=pd.read_csv(loc,header=None,sep=' ')
    p_y=dt.predict(X=t.iloc[:,1:101])
    ddf['mon_'+str(i)]=p_y
ddf

# %%
ddf.describe()

# %%
grade=[]
for i in range(0,200):
    val=ddf.iloc[i,1:13].values
    if 1 not in val:
        grade+='A'
    else:
        for j in range(11,-1,-1):
            if val[j]==1:
                j+=2
                break
        if j<=3:
            grade+='B'
        elif j<=6:
            grade+='C'
        else:
            grade+='D'
ddf['grade']=grade
ddf

# %%
ddf.rename(columns={0:'id'},inplace=True)

# %%
ans=ddf[ddf['mon_12']==0][['id','grade']]
ans.to_csv('附件5.csv')

# %%
plt.figure(figsize=(10,10))
sns.countplot(x=df_1[102])
plt.xlabel('predict')
plt.savefig('3.jpg')