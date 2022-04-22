--
-- PostgreSQL database dump
--

-- Dumped from database version 11.10 (Debian 11.10-astra.se3)
-- Dumped by pg_dump version 11.10 (Debian 11.10-astra.se3)

-- Started on 2022-01-06 02:25:12 MSK

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET escape_string_warning = off;
SET row_security = off;

--
-- TOC entry 2927 (class 1262 OID 16384)
-- Dependencies: 2926
-- Name: DATABASE hevaadb; Type: MAC LABEL; Schema: -; Owner: postgres
--

-- MAC LABEL ON DATABASE CURRENT_CATALOG IS '{0,0}';


--
-- TOC entry 2928 (class 1262 OID 16384)
-- Dependencies: 2926
-- Name: DATABASE hevaadb; Type: MAC CCR; Schema: -; Owner: postgres
--

--MAC CCR ON DATABASE CURRENT_CATALOG IS ON;


--
-- TOC entry 2929 (class 2615 OID 2200)
-- Dependencies: 3
-- Name: SCHEMA public; Type: MAC LABEL; Schema: -; Owner: postgres
--

-- MAC LABEL ON SCHEMA public IS '{0,0}';


--
-- TOC entry 2930 (class 2615 OID 2200)
-- Dependencies: 3
-- Name: SCHEMA public; Type: MAC CCR; Schema: -; Owner: postgres
--

-- MAC CCR ON SCHEMA public IS ON;


SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 196 (class 1259 OID 16401)
-- Name: he_raw; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.he_raw (
    id bigint NOT NULL,
    msg_datetime timestamp with time zone NOT NULL,
    raw_msg text,
    user_name character varying NOT NULL
);
-- WITH (MACS=FALSE);


ALTER TABLE public.he_raw OWNER TO postgres;

--
-- TOC entry 2931 (class 0 OID 0)
-- Dependencies: 196
-- Name: TABLE he_raw; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE public.he_raw IS 'Сырые данные';


--
-- TOC entry 2932 (class 0 OID 0)
-- Dependencies: 196
-- Name: COLUMN he_raw.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN public.he_raw.id IS 'Идентификатор';


--
-- TOC entry 2933 (class 0 OID 0)
-- Dependencies: 196
-- Name: COLUMN he_raw.msg_datetime; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN public.he_raw.msg_datetime IS 'Время получения сырого сообщения';


--
-- TOC entry 2934 (class 0 OID 0)
-- Dependencies: 196
-- Name: COLUMN he_raw.raw_msg; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN public.he_raw.raw_msg IS 'Сырое сообщение';


--
-- TOC entry 2935 (class 0 OID 0)
-- Dependencies: 196
-- Name: COLUMN he_raw.user_name; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN public.he_raw.user_name IS 'Имя пользователя';


--
-- TOC entry 2936 (class 1259 OID 16401)
-- Dependencies: 196
-- Name: TABLE he_raw; Type: MAC LABEL; Schema: public; Owner: postgres
--

--MAC LABEL ON TABLE public.he_raw IS '{0,0}';


--
-- TOC entry 2937 (class 1259 OID 16401)
-- Dependencies: 196
-- Name: TABLE he_raw; Type: MAC CCR; Schema: public; Owner: postgres
--

--MAC CCR ON TABLE public.he_raw IS ON;


--
-- TOC entry 197 (class 1259 OID 16404)
-- Name: he_raw_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.he_raw_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.he_raw_id_seq OWNER TO postgres;

--
-- TOC entry 2938 (class 0 OID 0)
-- Dependencies: 197
-- Name: he_raw_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.he_raw_id_seq OWNED BY public.he_raw.id;


--
-- TOC entry 2939 (class 1259 OID 16404)
-- Dependencies: 197
-- Name: SEQUENCE he_raw_id_seq; Type: MAC LABEL; Schema: public; Owner: postgres
--

--MAC LABEL ON SEQUENCE public.he_raw_id_seq IS '{0,0}';


--
-- TOC entry 2940 (class 1259 OID 16404)
-- Dependencies: 197
-- Name: SEQUENCE he_raw_id_seq; Type: MAC CCR; Schema: public; Owner: postgres
--

--MAC CCR ON SEQUENCE public.he_raw_id_seq IS ON;


--
-- TOC entry 2799 (class 2604 OID 16406)
-- Name: he_raw id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.he_raw ALTER COLUMN id SET DEFAULT nextval('public.he_raw_id_seq'::regclass);


-- Completed on 2022-01-06 02:25:12 MSK

--
-- PostgreSQL database dump complete
--

