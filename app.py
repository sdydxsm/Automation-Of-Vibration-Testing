import streamlit as st 
import pandas as pd
from streamlit_js_eval import streamlit_js_eval
import joblib


model = joblib.load('XGBClassifier_model.pkl')

hide_streamlit_style = """
<style>
    #root > div:nth-child(1) > div > div > div > div > section > div {padding-top: 0rem;}
    header {visibility: hidden;}
    [data-testid="stToolbar"] {visibility: hidden !important;}
            footer {visibility: hidden !important;}
</style>

"""

st.markdown(hide_streamlit_style, unsafe_allow_html=True)

st.title('Enter satellite acceleration data')

lx = st.number_input('linear x')
ly = st.number_input('linear y')
lz = st.number_input('linear z')
rx = st.number_input('rotational x')
ry = st.number_input('rotational y')
rz = st.number_input('rotational z')
average = (lx + ly + lz + rx + ry + rz) / 6



if st.button('Launch'):
    vibrations_data = [[lx, ly, lz, rx, ry, rz, average]]
    vibrations_data = pd.DataFrame(vibrations_data, columns=['linear_x' , 'linear_y' ,' linear_z' , 'rotational_x' , 'rotational_y' , 'rotational_z' , 'Average'])
    vibrations_data = vibrations_data.astype('float32')
    st.write(vibrations_data)
    predict = model.predict(vibrations_data)
    predict = 0 if predict<0.5 else 1 
    result = 'The satellite is correct' if predict == 1 else 'The satellite is faulty'
    st.title(result)

if st.button("Launch again"):
    streamlit_js_eval(js_expressions="parent.window.location.reload()") 