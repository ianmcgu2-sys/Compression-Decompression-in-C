#lang racket

(define (decompress)
  (decompress-h '()))

(define (decompress-h L)
  (define ch (peek-char))
  (if (eof-object? ch) (void)
      (local
        [(define rw (list->string (read-word)))]
        (cond
          [(char-whitespace? ch) (display (read-char)) (decompress-h L)]
          [(char-alphabetic? ch) (display rw)
                                 (decompress-h (cons (list rw (length L)) L))]
          [else (display (getword (getint) L)) (decompress-h L)]))))

(define (read-word)
  (define nc (peek-char))
  (if (char-alphabetic? nc)
      (cons (read-char) (read-word))
      empty))

(define (getint)
  (define (getint-h acc)
    (local [(define c (peek-char))]
      (if (char-numeric? c) (getint-h (+ (- (char->integer (read-char)) 48) (* 10 acc)))
        acc)))
    (getint-h 0))

(define (getword num lst)
  (if (= num (second (first lst)))
      (first (first lst))
      (getword num (rest lst))))

(decompress)