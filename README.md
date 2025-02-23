﻿# SentimentAnalysisService

Sentiment (tonality) and opinion mining analysis in Russian texts / Определение тональности и выделение высказываний в тексте на русском языке.

Эмоциональная оценка, выраженная в тексте, также называется тональностью, или сентиментом текста (от англ. sentiment — чувство; мнение, настроение). Эмоциональная составляющая, выраженная на уровне лексемы или коммуникативного фрагмента3, называется лексической тональностью (или лексическим сентиментом). Тональность текста в целом определяется лексической тональностью составляющих его единиц и правилами их сочетания.

Автоматическое определение тональности текста подразумевает выделение тех фрагментов текста, которые выражают позитивную или негативную
эмоциональность по отношению к объекту эмоциональной оценки (объекту тональности). Таким объектом может быть имя собственное, название продукта, организации, услуги, профессии и т. п., по отношению к которому анализируется текст. Объект эмоциональной оценки может быть задан как один в целом для текста (с учетом его синонимических и анафорических употреблений), так и определяться в предложениях как любое имя собственное или даже нарицательное. Таким образом, тональность текста определяется тремя факторами: 
1) субъект тональности; 
2) собственно тональная оценка (позитив/нейтрально/негатив); 
3) объект тональности. 
Под субъектом тональности подразумевается автор статьи (автор цитаты, прямой или косвенной речи), под объектом тональности — тот, о ком он высказывается и под тональной оценкой — эмоциональное отношение автора к такому объекту.

Анализ тональности текста, реализуемый данной системой, состоит из нескольких этапов. Сначала отрабатывает отдельный лингвистический модуль, автоматически производящий морфологический анализ текста, лемматизацию всей лексики и определяющий части речи каждого слова, его морфологические характеристики (падеж, лицо, число, активность-пассивность для глаголов), роль этого слова в предложении (для существительных: подлежащие, обстоятельство, дополнение; для глаголов: причастие, деепричастие, глагол; и др.), его тип (например, для существительных: физическое лицо, юридическое лицо, географическое название и др.).
Затем все слова (существительные, глаголы, прилагательные и наречия) и некоторые словосочетания (коллокации) размечаются по заранее подготовленным словарным спискам тональной лексики. Каждому слову приписывается два атрибута, указывающие на тональность и/или силу тональности. Если слово не нашлось в списках тональной лексики, то оно считается нейтральным.
После этого запускается первичный синтаксический анализ: слова и словосочетания объединяются в тональные цепочки, в предложении выделяются субъект, предикат и объект, идентифицируются причастные и деепричастные обороты, подчинительные предложения, анафорические связи и пр. Естественно, не каждое предложение русского языка можно представить в виде триады субъект-предикат-объект. Учитываются также безличные, неопределенно-личные и обобщенно-личные предложения, предложения с нулевой формой глагола, сказуемые, выраженные неглагольной формой.
На последнем этапе в предложении выделяется объект тональности и определяется его сентимент в зависимости от местоположения и роли этого
объекта в предложении.

##### view-1:
![alt tag](https://github.com/elzin/SentimentAnalysisService-demo/blob/master/demo-img-1.png)

##### view-2:
![alt tag](https://github.com/elzin/SentimentAnalysisService-demo/blob/master/demo-img-2.png)
