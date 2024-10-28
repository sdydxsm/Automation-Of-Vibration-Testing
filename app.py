import streamlit as st 
import pandas as pd
from streamlit_js_eval import streamlit_js_eval
from tensorflow import keras
from keras.models import load_model


model = load_model('vibration_model.h5')

hide_streamlit_style = """
<style>
    #root > div:nth-child(1) > div > div > div > div > section > div {padding-top: 0rem;}
    header {visibility: hidden;}
    [data-testid="stToolbar"] {visibility: hidden !important;}
            footer {visibility: hidden !important;}
</style>

"""

st.markdown(hide_streamlit_style, unsafe_allow_html=True)
# st.title('Наша модель выявит неисправность космического аппарата с помощью введенных вами данных')

st.title('Введите данные про ускорения')

lx = st.number_input('linear x')
ly = st.number_input('linear y')
lz = st.number_input('linear z')
rx = st.number_input('rotational x')
ry = st.number_input('rotational y')
rz = st.number_input('rotational z')
average = (lx + ly + lz + rx + ry + rz) / 6



if st.button('Запуск'):
    vibrations_data = [[lx, ly, lz, rx, ry, rz, average]]
    vibrations_data = pd.DataFrame(vibrations_data, columns=['linear_x' , 'linear_y' ,' linear_z' , 'rotational_x' , 'rotational_y' , 'rotational_z' , 'Average'])
    vibrations_data = vibrations_data.astype('float32')
    st.write(vibrations_data)
    predict = model.predict(vibrations_data)
    predict = 0 if predict<0.5 else 1 
    result = 'Космический аппарат исправен' if predict == 1 else 'Космический аппарат неисправен'
    st.title(result)

if st.button("Начать заново"):
    streamlit_js_eval(js_expressions="parent.window.location.reload()") 