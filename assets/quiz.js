/* ============================================================
   quiz.js — PX4 课程共享测验组件(无依赖,原生 JS)
   用法:在 HTML 中放置
     <div class="quiz" data-shuffle="true"
          data-questions='[
            {"q":"问题文本",
             "options":["选项A","选项B","选项C"],
             "answer":0,
             "explain":"答错后显示的解释"}
          ]'></div>
   并引入 <script src="../assets/quiz.js"></script>
   说明:answer 是 options 数组中的下标。data-shuffle 会打乱
   选项顺序(正确答案位置也会被移动),适合复习防死记位置。
   ============================================================ */
(function () {
	'use strict';

	function shuffle(arr, seedRandom) {
		var a = arr.slice();
		for (var i = a.length - 1; i > 0; i--) {
			var j = Math.floor(seedRandom() * (i + 1));
			var t = a[i]; a[i] = a[j]; a[j] = t;
		}
		return a;
	}

	// 简单可复现随机数(可选,便于打印版稳定)
	function makeRng(seed) {
		var s = seed >>> 0 || 1;
		return function () {
			s = (s * 1664525 + 1013904223) >>> 0;
			return s / 4294967296;
		};
	}

	function renderQuiz(el) {
		var questions;
		try {
			questions = JSON.parse(el.getAttribute('data-questions'));
		} catch (e) {
			el.textContent = '测验数据解析失败:' + e.message;
			return;
		}
		var doShuffle = el.getAttribute('data-shuffle') !== 'false';
		var rng = makeRng(questions.length * 7919 + 13);
		var total = questions.length;
		var answered = 0;
		var correctCount = 0;

		var scoreEl = document.createElement('div');
		scoreEl.className = 'quiz-score';

		questions.forEach(function (q, qi) {
			var card = document.createElement('div');
			card.className = 'quiz-question';

			var qtext = document.createElement('div');
			qtext.className = 'q-text';
			qtext.innerHTML = '<span class="q-num">Q' + (qi + 1) + '</span>' + escapeHtml(q.q);
			card.appendChild(qtext);

			// 构造 [{text, isCorrect}] 并可选打乱
			var items = q.options.map(function (opt, oi) {
				return { text: opt, isCorrect: oi === q.answer };
			});
			if (doShuffle) items = shuffle(items, rng);

			var list = document.createElement('ul');
			list.className = 'quiz-options';
			var keys = ['A', 'B', 'C', 'D', 'E', 'F'];
			var buttons = [];

			var feedback = document.createElement('div');
			feedback.className = 'quiz-feedback';

			items.forEach(function (item, ii) {
				var li = document.createElement('li');
				var btn = document.createElement('button');
				btn.type = 'button';
				btn.innerHTML = '<span class="key">' + keys[ii] + '</span>' + escapeHtml(item.text);
				btn.addEventListener('click', function () {
					if (btn.disabled) return;
					answered++;
					buttons.forEach(function (b) { b.disabled = true; });
					if (item.isCorrect) {
						btn.classList.add('correct');
						correctCount++;
						feedback.className = 'quiz-feedback show ok';
						feedback.textContent = '正确!';
					} else {
						btn.classList.add('wrong');
						// 高亮正确项
						items.forEach(function (it, j) {
							if (it.isCorrect) buttons[j].classList.add('correct');
						});
						feedback.className = 'quiz-feedback show err';
						feedback.textContent = q.explain
							? '再想想。' + q.explain
							: '再想想。';
					}
					if (answered === total) {
						scoreEl.textContent = '本测验得分:' + correctCount + ' / ' + total +
							(correctCount === total ? ' —— 全部答对,可以进入下一步。' : ' —— 建议重读本课相关段落后再继续。');
						scoreEl.classList.add('show');
					}
				});
				buttons.push(btn);
				li.appendChild(btn);
				list.appendChild(li);
			});

			card.appendChild(list);
			card.appendChild(feedback);
			el.appendChild(card);
		});
		el.appendChild(scoreEl);
	}

	function escapeHtml(s) {
		return String(s).replace(/[&<>"']/g, function (c) {
			return { '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;' }[c];
		});
	}

	document.addEventListener('DOMContentLoaded', function () {
		var quizzes = document.querySelectorAll('.quiz');
		for (var i = 0; i < quizzes.length; i++) renderQuiz(quizzes[i]);
	});
})();
