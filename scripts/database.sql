-- Create table
DROP TABLE IF EXISTS schema CASCADE;

-- id Идентификатор элемента
-- id_up Идентификатор родительского элемента
-- type Тип элемента. Принимает значения: 1, 2, 3
-- name Наименование
-- size Размер

CREATE TABLE schema(
    id UUID DEFAULT uuid_generate_v4() PRIMARY KEY NOT NULL,
    id_up UUID,
    type INTEGER NOT NULL,
    name TEXT NOT NULL,
    size INTEGER
);

-- Fill table
INSERT INTO schema (id_up, type, name, size) VALUES(null, 1, 'Контейнер 1', null);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 1'), 2, 'Объект 1', 101); 
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 1'), 3, 'Объект 2', 101);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 1'), 2, 'Объект 3', 101);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 1'), 3, 'Объект 4', 101);

INSERT INTO schema (id_up, type, name, size) VALUES(null, 1, 'Контейнер 2', null);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 2'), 2, 'Объект 5', 102);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 2'), 3, 'Объект 6', 102);

INSERT INTO schema (id_up, type, name, size) VALUES(null, 1, 'Контейнер 3', null);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 3'), 2, 'Объект 10', 102);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 3'), 1, 'Контейнер 4', null);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 4'), 2, 'Объект 7', 104);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 4'), 3, 'Объект 8', 104);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 4'), 3, 'Объект 9', 104);

INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 3'), 1, 'Контейнер 5', 102);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 5'), 3, 'Объект 11', 104);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 5'), 2, 'Объект 12', 104);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 3'), 2, 'Объект 13', 102);
INSERT INTO schema (id_up, type, name, size) VALUES((SELECT id FROM schema WHERE name='Контейнер 3'), 2, 'Объект 14', 102);