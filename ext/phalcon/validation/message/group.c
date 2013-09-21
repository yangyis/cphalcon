
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Validation\Message\Group
 *
 * Represents a group of validation messages
 */
ZEPHIR_INIT_CLASS(Phalcon_Validation_Message_Group) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Validation\\Message, Group, phalcon, validation_message_group, phalcon_validation_message_group_method_entry, 0);

	zend_declare_property_null(phalcon_validation_message_group_ce, SL("_position"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_validation_message_group_ce, SL("_messages"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Phalcon\Validation\Message\Group constructor
 *
 * @param array messages
 */
PHP_METHOD(Phalcon_Validation_Message_Group, __construct) {

	zval *messages = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &messages);

	if (!messages) {
		ZEPHIR_CPY_WRT(messages, ZEPHIR_GLOBAL(global_null));
	}


	if ((Z_TYPE_P(messages) == IS_ARRAY)) {
		zephir_update_property_this(this_ptr, SL("_messages"), messages TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Gets an attribute a message using the array syntax
 *
 *<code>
 * print_r($messages[0]);
 *</code>
 *
 * @param string index
 * @return Phalcon\Validation\Message
 */
PHP_METHOD(Phalcon_Validation_Message_Group, offsetGet) {

	zval *index, *messages, *message;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index);



	ZEPHIR_OBS_VAR(messages);
	zephir_read_property_this(&messages, this_ptr, SL("_messages"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(message);
	if (zephir_array_isset_fetch(&message, messages, index TSRMLS_CC)) {
		RETURN_CCTOR(message);
	}
	RETURN_MM_NULL();

}

/**
 * Sets an attribute using the array-syntax
 *
 *<code>
 * $messages[0] = new Phalcon\Validation\Message('This is a message');
 *</code>
 *
 * @param string index
 * @param Phalcon\Validation\Message message
 */
PHP_METHOD(Phalcon_Validation_Message_Group, offsetSet) {

	zval *index, *message;

	zephir_fetch_params(0, 2, 0, &index, &message);



	if ((Z_TYPE_P(message) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_STRW(phalcon_validation_exception_ce, "The message must be an object");
		return;
	}
	zephir_update_property_array(this_ptr, SL("_messages"), index, message TSRMLS_CC);

}

/**
 * Checks if an index exists
 *
 *<code>
 * var_dump(isset($message['database']));
 *</code>
 *
 * @param string index
 * @return boolean
 */
PHP_METHOD(Phalcon_Validation_Message_Group, offsetExists) {

	zval *index, *messages;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index);



	ZEPHIR_OBS_VAR(messages);
	zephir_read_property_this(&messages, this_ptr, SL("_messages"), PH_NOISY_CC);
	RETURN_MM_BOOL(zephir_array_isset(messages, index));

}

/**
 * Removes a message from the list
 *
 *<code>
 * unset($message['database']);
 *</code>
 *
 * @param string index
 */
PHP_METHOD(Phalcon_Validation_Message_Group, offsetUnset) {

	zval *index, *messages;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index);



	ZEPHIR_OBS_VAR(messages);
	zephir_read_property_this(&messages, this_ptr, SL("_messages"), PH_NOISY_CC);
	if (zephir_array_isset(messages, index)) {
	}
	RETURN_MM_BOOL(0);

}

/**
 * Appends a message to the group
 *
 *<code>
 * $messages->appendMessage(new Phalcon\Validation\Message('This is a message'));
 *</code>
 *
 * @param Phalcon\Validation\MessageInterface message
 */
PHP_METHOD(Phalcon_Validation_Message_Group, appendMessage) {

	zval *message;

	zephir_fetch_params(0, 1, 0, &message);



	if ((Z_TYPE_P(message) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_STRW(phalcon_validation_exception_ce, "The message must be an object");
		return;
	}
	zephir_update_property_array_append(this_ptr, SL("_messages"), message TSRMLS_CC);

}

/**
 * Appends an array of messages to the group
 *
 *<code>
 * $messages->appendMessages($messagesArray);
 *</code>
 *
 * @param Phalcon\Validation\MessageInterface[] messages
 */
PHP_METHOD(Phalcon_Validation_Message_Group, appendMessages) {

	HashTable *_2;
	HashPosition _1;
	zval *messages, *currentMessages, *finalMessages = NULL, *message = NULL, *_0, **_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &messages);



	if ((Z_TYPE_P(messages) != IS_ARRAY)) {
		if ((Z_TYPE_P(messages) != IS_OBJECT)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_validation_exception_ce, "The messages must be array or object");
			return;
		}
	}
	ZEPHIR_OBS_VAR(currentMessages);
	zephir_read_property_this(&currentMessages, this_ptr, SL("_messages"), PH_NOISY_CC);
	if ((Z_TYPE_P(messages) == IS_ARRAY)) {
		if (ZEPHIR_IS_STRING(currentMessages, "array")) {
			ZEPHIR_INIT_VAR(finalMessages);
			zephir_fast_array_merge(finalMessages, &(currentMessages), &(messages) TSRMLS_CC);
		} else {
			ZEPHIR_CPY_WRT(finalMessages, messages);
		}
		zephir_update_property_this(this_ptr, SL("_messages"), finalMessages TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_0);
		zephir_call_func_p1(_0, "iterator", messages);
		zephir_is_iterable(_0, &_2, &_1, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
			; zend_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HVALUE(message, _3);
			zephir_call_method_p1_noret(this_ptr, "appendmessage", message);
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Filters the message group by field name
 *
 * @param string fieldName
 * @return array
 */
PHP_METHOD(Phalcon_Validation_Message_Group, filter) {

	HashTable *_1;
	HashPosition _0;
	zval *fieldName, *filtered, *messages, *message = NULL, **_2, _3 = zval_used_for_init, *_4 = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &fieldName);



	ZEPHIR_INIT_VAR(filtered);
	array_init(filtered);
	ZEPHIR_OBS_VAR(messages);
	zephir_read_property_this(&messages, this_ptr, SL("_messages"), PH_NOISY_CC);
	if ((Z_TYPE_P(messages) == IS_ARRAY)) {
		zephir_is_iterable(messages, &_1, &_0, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
			; zend_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HVALUE(message, _2);
			ZEPHIR_SINIT_NVAR(_3);
			ZVAL_STRING(&_3, "getField", 0);
			ZEPHIR_INIT_NVAR(_4);
			zephir_call_func_p2(_4, "method_exists", message, &_3);
			if (zephir_is_true(_4)) {
				ZEPHIR_INIT_NVAR(_5);
				zephir_call_method(_5, message, "getfield");
				if (ZEPHIR_IS_EQUAL(fieldName, _5)) {
					zephir_array_append(&filtered, message, PH_SEPARATE);
				}
			}
		}
	}
	RETURN_CCTOR(filtered);

}

/**
 * Returns the number of messages in the list
 *
 * @return int
 */
PHP_METHOD(Phalcon_Validation_Message_Group, count) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_messages"), PH_NOISY_CC);
	RETURN_LONG(zephir_fast_count_int(_0 TSRMLS_CC));

}

/**
 * Rewinds the internal iterator
 */
PHP_METHOD(Phalcon_Validation_Message_Group, rewind) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 0);
	zephir_update_property_this(this_ptr, SL("_position"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the current message in the iterator
 *
 * @return Phalcon\Validation\Message
 */
PHP_METHOD(Phalcon_Validation_Message_Group, current) {

	zval *messages, *message, *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(messages);
	zephir_read_property_this(&messages, this_ptr, SL("_messages"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(message);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_position"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&message, messages, _0 TSRMLS_CC)) {
		RETURN_CCTOR(message);
	}
	RETURN_MM_NULL();

}

/**
 * Returns the current position/key in the iterator
 *
 * @return int
 */
PHP_METHOD(Phalcon_Validation_Message_Group, key) {


	RETURN_MEMBER(this_ptr, "_position");

}

/**
 * Moves the internal iteration pointer to the next position
 *
 */
PHP_METHOD(Phalcon_Validation_Message_Group, next) {



}

/**
 * Check if the current message in the iterator is valid
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Validation_Message_Group, valid) {

	zval *messages, *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(messages);
	zephir_read_property_this(&messages, this_ptr, SL("_messages"), PH_NOISY_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_position"), PH_NOISY_CC);
	RETURN_MM_BOOL(zephir_array_isset(messages, _0));

}

/**
 * Magic __set_state helps to re-build messages variable when exporting
 *
 * @param array group
 * @return Phalcon\Mvc\Model\Message\Group
 */
PHP_METHOD(Phalcon_Validation_Message_Group, __set_state) {

	zval *group, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &group);



	object_init_ex(return_value, phalcon_validation_message_group_ce);
	ZEPHIR_OBS_VAR(_0);
	zephir_array_fetch_string(&_0, group, SL("_messages"), PH_NOISY TSRMLS_CC);
	zephir_call_method_p1_noret(return_value, "__construct", _0);
	RETURN_MM();

}
