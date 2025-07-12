
import numpy as np
from sklearn.ensemble import RandomForestClassifier
import joblib

X = np.array([
    [0, 0, 20],
    [5, 2, 50],
    [10, 4, 25],
    [15, 7, 80]
])

y = np.array([0, 3, 1, 3])

model = RandomForestClassifier(n_estimators=100)
model.fit(X, y)

joblib.dump(model, 'navigation_model.pkl')
